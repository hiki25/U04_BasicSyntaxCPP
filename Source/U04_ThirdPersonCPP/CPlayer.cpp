#include "CPlayer.h"
#include "Global.h"
#include "Assingment/CBoxBase_Box.h"
#include "Assingment/CBoxBase_Door.h"
#include "Assingment/CKey.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "CAnimInstance.h"
#include "CWeapone.h"
#include "Widgets/CCrossHairWidget.h"

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

<<<<<<< Updated upstream
}

void ACPlayer::ChangeSpeed(float InMoveSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = InMoveSpeed;
=======
	Key = CreateDefaultSubobject<ACKey>("Key");

>>>>>>> Stashed changes
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
<<<<<<< Updated upstream

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
=======
	OnActorBeginOverlap.AddDynamic(this, &ACPlayer::ActorBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &ACPlayer::ActorEndOverlap);

	
>>>>>>> Stashed changes
}


void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

<<<<<<< Updated upstream
=======
	PlayerInputComponent->BindAction("Open", EInputEvent::IE_Pressed, this, &ACPlayer::OnOpen);
>>>>>>> Stashed changes
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &ACPlayer::OnSprint);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &ACPlayer::OffSprint);

	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Pressed, this, &ACPlayer::OnAim);
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Released, this, &ACPlayer::OffAim);

	PlayerInputComponent->BindAction("Rifle", EInputEvent::IE_Pressed, this, &ACPlayer::ToggleEquip);
}

void ACPlayer::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	ACBoxBase_Box* OverlapBox = Cast<ACBoxBase_Box>(OtherActor);
	if(OverlapBox != nullptr)
	{
		Box = OverlapBox;
	}

	ACBoxBase_Door* OverlapDoor = Cast<ACBoxBase_Door>(OtherActor);
	if (OverlapDoor != nullptr)
	{
		Door = OverlapDoor;
	}
	
}

void ACPlayer::ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Box = nullptr;
	Door = nullptr;
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
<<<<<<< Updated upstream
	if (Weapone == nullptr) return;

	if (Weapone->IsEquipped())
	{
		Weapone->UnEquip();
	}
	else
	{
		Weapone->Equip();
	}
}

void ACPlayer::OnAim()
{
	if (Weapone == nullptr) return;
	if (Weapone->IsEquipped() == false) return;
	if (Weapone->IsEquipping() == true) return;

	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	SpringArmComp->TargetArmLength = 100.0f;
	SpringArmComp->SocketOffset = FVector(0, 30, 10);

	Begin_Zoom();

	Weapone->BeginAiming();
}

void ACPlayer::OffAim()
{
	if (Weapone == nullptr) return;
	if (Weapone->IsEquipped() == false) return;
	if (Weapone->IsEquipping() == true) return;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	SpringArmComp->TargetArmLength = 200.0f;
	SpringArmComp->SocketOffset = FVector(0, 60, 0);

	End_Zoom();
	Weapone->EndAiming();
}

void ACPlayer::SetBodyColor(FLinearColor InBodyColor, FLinearColor InLogoColor)
{
	BodyMaterial->SetVectorParameterValue("BodyColor", InBodyColor);
	LogoMaterial->SetVectorParameterValue("BodyColor", InLogoColor);
}

=======
	GetWorldTimerManager().SetTimer(fTimerHandler, this, &ACPlayer::OnOpen, 0.03f, false, 0.00f);
	if (Box != nullptr)
	{
		float Start = 0.00f;
		float End = 90.f;
		float Alpha = timeDelta;

		float Result = UKismetMathLibrary::Lerp(Start, End, Alpha);
		Box->OpenTheDoor(Result);
	}
	
	

	if (Door != nullptr)
	{
		float Start = 0.00f;
		float End = 90.f;
		float Alpha = timeDelta;

		float Result = UKismetMathLibrary::Lerp(Start, End, Alpha);
		Door->OpenTheDoor(Result);
	}
	if (timeDelta > 1.0f)
	{
		GetWorldTimerManager().ClearTimer(fTimeHandler);
	}
}

void ACPlayer::Tick(float DeltaSeconds)
{
	CLog::Print("RedKey : " + FString::FromInt(Key->GetRedKey()),1,10.0F,FColor::Red);
	CLog::Print("GreenKey : " + FString::FromInt(Key->GetGreenKey()),2, 10.0F, FColor::Green);
	CLog::Print("BlueKey : " + FString::FromInt(Key->GetBlueKey()), 3, 10.0F, FColor::Blue);
	timeDelta += DeltaSeconds;
}

>>>>>>> Stashed changes
