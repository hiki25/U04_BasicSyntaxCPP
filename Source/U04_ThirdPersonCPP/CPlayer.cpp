#include "CPlayer.h"
#include "Global.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "CAnimInstance.h"
#include "CWeapone.h"
#include "Widgets/CCrossHairWidget.h"
#include "Widgets/CAutoWidget.h"

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(GetCapsuleComponent());
	SpringArmComp->SetRelativeLocation(FVector(0, 0, 60));
	SpringArmComp->TargetArmLength = 200.f;
	SpringArmComp->bDoCollisionTest = false;
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SocketOffset = FVector(0, 60, 0);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 400.f;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> meshAsset(TEXT("SkeletalMesh'/Game/Character/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (meshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(meshAsset.Object);
	}

	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	ConstructorHelpers::FClassFinder<UCAnimInstance> AnimInstanceClass(TEXT("/Game/ABP_CPlayer"));
	if (AnimInstanceClass.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceClass.Class);
	}

	ConstructorHelpers::FClassFinder<UCCrossHairWidget> CrossHairWidgetClassAsset(TEXT("/Game/Wigets/WB_CrossHair"));
	if (CrossHairWidgetClassAsset.Succeeded())
	{
		CrossHairWidgetClass = CrossHairWidgetClassAsset.Class;
	}

	ConstructorHelpers::FClassFinder<UCAutoWidget> AutoWidgetClassAsset(TEXT("/Game/Wigets/WB_AutoWidget"));
	if (AutoWidgetClassAsset.Succeeded())
	{
		AutoWidgetClass = AutoWidgetClassAsset.Class;
	}


}

void ACPlayer::ChangeSpeed(float InMoveSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = InMoveSpeed;
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	BodyMaterial =UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(0), this);
	LogoMaterial =UMaterialInstanceDynamic::Create(GetMesh()->GetMaterial(1), this);

	GetMesh()->SetMaterial(0, BodyMaterial);
	GetMesh()->SetMaterial(1, LogoMaterial);

	FActorSpawnParameters SpawnParam;
	SpawnParam.Owner = this;
	SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	Weapone = GetWorld()->SpawnActor<ACWeapone>(WeaponeClass,SpawnParam);

	CrossHairWidget = CreateWidget<UCCrossHairWidget, APlayerController>(GetController<APlayerController>(), CrossHairWidgetClass);
	CrossHairWidget->AddToViewport();
	CrossHairWidget->SetVisibility(ESlateVisibility::Hidden);

	AutoWidget = CreateWidget<UCAutoWidget, APlayerController>(GetController<APlayerController>(), AutoWidgetClass);
	AutoWidget->AddToViewport();
}

void ACPlayer::Tick(float Deltatime)
{
	CurrentBullet = Weapone->GetCurrentBullet();
	MaxBullet = Weapone->GetMaxBullet();
	AutoWidget->BulletCount(MaxBullet, CurrentBullet);
}


void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &ACPlayer::OnSprint);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &ACPlayer::OffSprint);

	PlayerInputComponent->BindAction("AutoFire", EInputEvent::IE_Pressed, this, &ACPlayer::ToggleAuto);

	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Pressed, this, &ACPlayer::OnAim);
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Released, this, &ACPlayer::OffAim);

	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &ACPlayer::OnFire);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Released, this, &ACPlayer::OffFire);

	PlayerInputComponent->BindAction("Rifle", EInputEvent::IE_Pressed, this, &ACPlayer::ToggleEquip);

	PlayerInputComponent->BindAction("Reload", EInputEvent::IE_Pressed, this, &ACPlayer::Reload);
}

void ACPlayer::OnTarget()
{
	CrossHairWidget->OnTarget();
}

void ACPlayer::OffTarget()
{
	CrossHairWidget->OffTarget();
}

void ACPlayer::OnMoveForward(float Axis)
{
	FRotator ControlRotation = FRotator(0, GetControlRotation().Yaw,0);
	FVector direction = FQuat(ControlRotation).GetForwardVector();

	AddMovementInput(direction, Axis);
}

void ACPlayer::OnMoveRight(float Axis)
{
	FRotator ControlRotation = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(ControlRotation).GetRightVector();

	AddMovementInput(direction, Axis);
}

void ACPlayer::OnSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 600.f;
}

void ACPlayer::OffSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
}

void ACPlayer::ToggleEquip()
{
	if (Weapone == nullptr) return;

	if (Weapone->IsEquipped())
	{
		OffAim();
		Weapone->UnEquip();
	}
	else
	{
		Weapone->Equip();
	}
	Weapone->End_Fire();
}

void ACPlayer::ToggleAuto()
{
	if (Weapone->IsFiring() == true) return;
	Weapone->ToggleAutoFire();

	(Weapone->IsAutoFire() ? AutoWidget->OnAuto() : AutoWidget->OffAuto());
}

void ACPlayer::OnAim()
{
	
	if (Weapone == nullptr) return;
	if (Weapone->IsEquipped() == false) return;
	if (Weapone->IsEquipping() == true) return;
	if (Weapone->IsReloading() == true) return;

	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	SpringArmComp->TargetArmLength = 100.0f;
	SpringArmComp->SocketOffset = FVector(0, 30, 10);

	Begin_Zoom();

	Weapone->BeginAiming();
	CrossHairWidget->SetVisibility(ESlateVisibility::Visible);
}

void ACPlayer::OffAim()
{
	
	if (Weapone == nullptr) return;
	if (Weapone->IsEquipped() == false) return;
	if (Weapone->IsEquipping() == true) return;
	if (Weapone->IsReloading() == true) return;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	SpringArmComp->TargetArmLength = 200.0f;
	SpringArmComp->SocketOffset = FVector(0, 60, 0);

	End_Zoom();
	Weapone->EndAiming();
	CrossHairWidget->SetVisibility(ESlateVisibility::Hidden);
}

void ACPlayer::OnFire()
{
	Weapone->Begin_Fire();
}

void ACPlayer::OffFire()
{
	Weapone->End_Fire();
}

void ACPlayer::Reload()
{
	if (Weapone == nullptr) return;
	if (Weapone->IsEquipped() == false) return;
	OffAim();
	OffFire();
	Weapone->RelaodBullet();
}

void ACPlayer::SetBodyColor(FLinearColor InBodyColor, FLinearColor InLogoColor)
{
	BodyMaterial->SetVectorParameterValue("BodyColor", InBodyColor);
	LogoMaterial->SetVectorParameterValue("BodyColor", InLogoColor);
}

void ACPlayer::GetAimInfo(FVector& OutAimStart, FVector& OutAimEnd, FVector& OutAimDirection)
{
	OutAimDirection = CameraComp->GetForwardVector();
	FVector MuzzleLocation = Weapone->GetMesh()->GetSocketLocation("MuzzleFlash");
	FVector CameraLocation = CameraComp->GetComponentToWorld().GetLocation();

	OutAimStart = CameraLocation+ OutAimDirection * (OutAimDirection | (MuzzleLocation - CameraLocation));

	FVector RandomConeDirection = UKismetMathLibrary::RandomUnitVectorInConeInDegrees(OutAimDirection, 0.2f);
	RandomConeDirection *= 50000.0f;
	OutAimEnd = CameraLocation + RandomConeDirection;
}

