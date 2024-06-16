#include "CPlayer.h"
#include "Global.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "CAnimInstance.h"
#include "Assingment/CBoxBase_Box.h"
#include "Assingment/CBoxBase_Door.h"
#include "Assingment/CKey.h"


ACPlayer::ACPlayer()
{
	PrimaryActorTick.bStartWithTickEnabled = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->SetupAttachment(GetCapsuleComponent());
	SpringArmComp->SetRelativeLocation(FVector(0, 0, 60));
	SpringArmComp->TargetArmLength = 200.f;
	SpringArmComp->bDoCollisionTest = false;
	SpringArmComp->bUsePawnControlRotation = true;

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


	

}

void ACPlayer::Tick(float DeltaSeconds)
{
	
	if (Key.Num() > 0)
	{
		CLog::Print(TEXT("Have " + Key[0].ToString() + " Key"), 1);
		if (Key.Num() > 1)
		{
			CLog::Print(TEXT("Have " + Key[1].ToString() + " Key"), 2);
			if (Key.Num() > 2)
			{
				CLog::Print(TEXT("Have " + Key[2].ToString() + " Key"), 3);
			}
		}
		
	}
		
	
}

void ACPlayer::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &ACPlayer::ActorBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &ACPlayer::ActorEndOverlap);
}


void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Open", EInputEvent::IE_Pressed, this, &ACPlayer::OnOpen);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Pressed, this, &ACPlayer::OnSprint);
	PlayerInputComponent->BindAction("Sprint", EInputEvent::IE_Released, this, &ACPlayer::OffSprint);
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


void ACPlayer::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	ACBoxBase_Box* OverlapBox = Cast<ACBoxBase_Box>(OtherActor);
	if (OverlapBox != nullptr)
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


void ACPlayer::OnOpen()
{
	if (Box != nullptr)
	{
		Box->OpenTheDoor(50.0f);
		Key.AddUnique(Box->GetName());
	}
	

	if (Door != nullptr )
	{
		if (Key.Find(Door->GetName())>-1)
		{
			Door->OpenTheDoor(90.0f);
		}
		else
		{
			CLog::Print(TEXT("You Don't Have Key"),-1,1.0f,FColor::Red);
		}
	}
	
	
	
}


