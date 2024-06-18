#include "CWeapone.h"
#include "Global.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "CWeaponeInterface.h"
#include "CPlayer.h"

static TAutoConsoleVariable<bool> CVarDebugLine(TEXT("Tore.DrawDebugLine"), false,TEXT("Enable Draw Aim Line"),ECVF_Cheat);

ACWeapone::ACWeapone()
{
	PrimaryActorTick.bCanEverTick = true;

	HolsterSoket = "Holster_AR4";
	HandSoket = "Hand_AR4";

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>("MeshComp");
	RootComponent = MeshComp;

	ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Game/Weapons/Meshes/AR4/SK_AR4"));
	if (MeshAsset.Succeeded())
	{
		MeshComp->SetSkeletalMesh(MeshAsset.Object);
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> EquipMontageAsset(TEXT("/Game/Character/Animations/AR4/Equip_Mongtage"));
	if (EquipMontageAsset.Succeeded())
	{
		EquipMontage = EquipMontageAsset.Object;
	}

	ConstructorHelpers::FObjectFinder<UAnimMontage> UnEquipMontageAsset(TEXT("/Game/Character/Animations/AR4/UnEquip_Mongtage"));
	if (UnEquipMontageAsset.Succeeded())
	{
		UnEquipMontage = UnEquipMontageAsset.Object;
	}

	ConstructorHelpers::FClassFinder<UCameraShake> CameraShakeAsset(TEXT("/Game/BP_FireShake.BP"));
	if(CameraShakeAsset.Succeeded())
	{
		CameraShakeClass = CameraShakeAsset.Class;
	}


}

void ACWeapone::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());

	if(OwnerCharacter)
	{
		AttachToComponent
		(
			OwnerCharacter->GetMesh(),
			FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
			HolsterSoket
		);
	}
	
	
}

void ACWeapone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bAiming == false)
	{
		return;
	}

	ICWeaponeInterface* ImplementedsActor = Cast<ICWeaponeInterface>(OwnerCharacter);
	if (ImplementedsActor == nullptr) return;
	
	FVector Start, End, Direction;
	ImplementedsActor->GetAimInfo(Start, End, Direction);
	
	bool bDrawDebug = CVarDebugLine.GetValueOnGameThread();

	if (bDrawDebug)
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, -1, 0, 2.f);
	}
	
	
	FCollisionQueryParams Param;
	Param.AddIgnoredActor(this);
	Param.AddIgnoredActor(OwnerCharacter);

	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_Visibility, Param))
	{
		if (Hit.Component->IsSimulatingPhysics())
		{

			ImplementedsActor->OnTarget();
			return;
		}
	}

	ImplementedsActor->OffTarget();

}

void ACWeapone::Equip()
{
	if (bEquipping == true) return;
	if (bEquipped == true) return;

	bEquipping = true;
	OwnerCharacter->PlayAnimMontage(EquipMontage);
}

void ACWeapone::Begin_Equip()
{
	bEquipped = true;

	AttachToComponent
	(
		OwnerCharacter->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		HandSoket
	);
}

void ACWeapone::End_Equip()
{
	bEquipping = false;
}

void ACWeapone::Begin_UnEquip()
{
	bEquipped = false;

	AttachToComponent
	(
		OwnerCharacter->GetMesh(),
		FAttachmentTransformRules(EAttachmentRule::KeepRelative, true),
		HolsterSoket
	);
}

void ACWeapone::End_UnEquip()
{
	bEquipping = false;
}

void ACWeapone::UnEquip()
{
	if (bEquipping == true) return;
	if (bEquipped == false) return;

	bEquipping = true;
	OwnerCharacter->PlayAnimMontage(UnEquipMontage);
}

void ACWeapone::BeginAiming()
{
	bAiming = true;
}

void ACWeapone::EndAiming()
{
	bAiming = false;
}

void ACWeapone::Begin_Fire()
{
	if (bEquipped == false) return;
	if (bEquipping == true) return;
	if (bAiming == false) return;
	if (bFiring == true) return;

	bFiring = true;

	Firing();
}

void ACWeapone::End_Fire()
{
	bFiring = false;
}

void ACWeapone::Firing()
{
	ACPlayer* Player = Cast<ACPlayer>(OwnerCharacter);
	if (Player)
	{
		APlayerController* PC = Player->GetController<APlayerController>();
		if (CameraShakeClass)
		{
			PC->PlayerCameraManager->PlayCameraShake(CameraShakeClass);
		}
	}

	ICWeaponeInterface* ImplementedsActor = Cast<ICWeaponeInterface>(OwnerCharacter);
	if (ImplementedsActor == nullptr) return;

	FVector Start, End, Direction;
	ImplementedsActor->GetAimInfo(Start, End, Direction);

	FCollisionQueryParams Param;
	Param.AddIgnoredActor(this);
	Param.AddIgnoredActor(OwnerCharacter);

	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_Visibility, Param))
	{
		if (Hit.Component->IsSimulatingPhysics())
		{
			Direction = Hit.Actor->GetActorLocation() - OwnerCharacter->GetActorLocation();
			Direction.Normalize();

			Hit.Component->AddImpulseAtLocation(Direction * 3000.0f,OwnerCharacter->GetActorLocation());
		}
	}
}
