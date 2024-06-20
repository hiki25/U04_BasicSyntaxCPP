#include "CWeapone.h"
#include "Global.h"
#include "CBullet.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/DecalComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Sound/SoundCue.h"
#include "GameFramework/Character.h"
#include "CWeaponeInterface.h"
#include "CPlayer.h"

static TAutoConsoleVariable<bool> CVarDebugLine(TEXT("Tore.DrawDebugLine"), false, TEXT("Enable Draw Aim Line"), ECVF_Cheat);

ACWeapone::ACWeapone()
{
	PrimaryActorTick.bCanEverTick = true;

	FireInterval = 0.1f;
	PitchSpeed = 0.25f;
	MaxBullet = 30;
	CurrentBullet = MaxBullet;

	HolsterSoket = "Holster_AR4";
	HandSoket = "Hand_AR4";

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>("MeshComp");
	RootComponent = MeshComp;

	MagEmtyComp = CreateDefaultSubobject<UStaticMeshComponent>("Mag_Empty");

	ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Game/Weapons/Meshes/AR4/SK_AR4"));
	if (MeshAsset.Succeeded())
	{
		MeshComp->SetSkeletalMesh(MeshAsset.Object);
	}

	ConstructorHelpers::FObjectFinder<UStaticMesh> MagEmtyMeshAsset(TEXT("/Game/Weapons/Meshes/AR4/SM_AR4_Mag_Empty"));
	if (MagEmtyMeshAsset.Succeeded())
	{
		MagEmtyComp->SetStaticMesh(MagEmtyMeshAsset.Object);
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

	ConstructorHelpers::FObjectFinder<UAnimMontage> ReloadMontageAsset(TEXT("AnimMontage'/Game/Character/Animations/AR4/Rifle_Jog_Reload_Montage.Rifle_Jog_Reload_Montage'"));
	if (ReloadMontageAsset.Succeeded())
	{
		ReloadMontage = ReloadMontageAsset.Object;
	}

	ConstructorHelpers::FClassFinder<UCameraShake> CameraShakeAsset(TEXT("/Game/BP_FireShake"));
	if (CameraShakeAsset.Succeeded())
	{
		CameraShakeClass = CameraShakeAsset.Class;
	}

	ConstructorHelpers::FObjectFinder<UMaterialInstanceConstant>MaterialAsset(TEXT("/Game/Materials/MI_Decal"));
	if (MaterialAsset.Succeeded())
	{
		Decal = MaterialAsset.Object;
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

	if (bAiming == false) return;

	ICWeaponeInterface* ImplementedActor = Cast<ICWeaponeInterface>(OwnerCharacter);
	if (ImplementedActor == nullptr) return;

	FVector Start, End, Direction;
	ImplementedActor->GetAimInfo(Start, End, Direction);

	bool bDrawDebug = CVarDebugLine.GetValueOnGameThread();

	if (bDrawDebug)
	{
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, -1, 0, 2.f);
	}

	FHitResult Hit;
	FCollisionQueryParams Param;
	Param.AddIgnoredActor(this);
	Param.AddIgnoredActor(OwnerCharacter);

	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_PhysicsBody, Param))
	{
		if (Hit.Component->IsSimulatingPhysics())
		{
			ImplementedActor->OnTarget();
			return;
		}
	}
	ImplementedActor->OffTarget();

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

void ACWeapone::Begin_Fire()
{
	if (bEquipped == false) return;
	if (bEquipping == true) return;
	if (bAiming == false) return;
	if (bFring == true) return;
	if (bReloading == true) return;
	bFring = true;

	CurrentPitch = 0;

	if (bAutoFire)
	{
		GetWorld()->GetTimerManager().SetTimer(AutoTimerHandel, this, &ACWeapone::OnFire, FireInterval, true, 0.f);
	}
	OnFire();
}

void ACWeapone::End_Fire()
{
	bFring = false;

	if (bAutoFire)
	{
		GetWorld()->GetTimerManager().ClearTimer(AutoTimerHandel);
	}
}

void ACWeapone::ToggleAutoFire()
{
	bAutoFire = !bAutoFire;
}

void ACWeapone::RelaodBullet()
{
	if (bReloading == true) return;
	OwnerCharacter->PlayAnimMontage(ReloadMontage);
}

void ACWeapone::Begin_Reload()
{
	bReloading = true;
	CurrentBullet = MaxBullet;
	GetMesh()->HideBoneByName(TEXT("b_gun_mag"), EPhysBodyOp::PBO_MAX);

}

void ACWeapone::End_Reload()
{
	bReloading = false;
	GetMesh()->UnHideBoneByName(TEXT("b_gun_mag"));
	MagEmtyComp->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
}


void ACWeapone::OnFire()
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

	CurrentBullet--;
	if (CurrentBullet == 0)
	{
		Player->Reload();
		return;
	}

	ICWeaponeInterface* ImplementedActor = Cast<ICWeaponeInterface>(OwnerCharacter);
	if (ImplementedActor == nullptr) return;
	FVector Start, End, Direction;
	ImplementedActor->GetAimInfo(Start, End, Direction);

	FVector MuzzleLocation = GetMesh()->GetSocketLocation("MuzzleFlash");
	if (Bulletclass)
	{
		GetWorld()->SpawnActor<ACBullet>(Bulletclass, MuzzleLocation,Direction.Rotation());
	}
	if (FireParticle)
	{
		UGameplayStatics::SpawnEmitterAttached(FireParticle,MeshComp,"MuzzleFlash");
	}
	if (EjectParticle)
	{
		UGameplayStatics::SpawnEmitterAttached(EjectParticle, MeshComp, "EjectBullet");
	}
	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSound, MuzzleLocation);
	}

	CurrentPitch -= PitchSpeed * GetWorld()->GetDeltaSeconds();
	if (CurrentPitch > -PitchSpeed)
	{
		OwnerCharacter->AddControllerPitchInput(CurrentPitch);
	}
	
	
	FHitResult Hit;
	FCollisionQueryParams Param;
	Param.AddIgnoredActor(this);
	Param.AddIgnoredActor(OwnerCharacter);

	if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECollisionChannel::ECC_PhysicsBody, Param))
	{

		FVector ImpactLocation = Hit.ImpactPoint;
		FRotator ImpactRotation = Hit.ImpactNormal.Rotation();

		if (Decal)
		{
			UDecalComponent* DecalComp = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), Decal, FVector(5), ImpactLocation, ImpactRotation, 3.0f);
			DecalComp->SetFadeScreenSize(0);
		}
		if (ImpactParticle)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),ImpactParticle,ImpactLocation,ImpactRotation);
		}

		if (Hit.Component->IsSimulatingPhysics())
		{
			Direction = Hit.Actor->GetActorLocation() - OwnerCharacter->GetActorLocation();
			Direction.Normalize();
			Hit.Component->AddImpulseAtLocation(Direction * 3000.0f, OwnerCharacter->GetActorLocation());
			return;
		}
	}
	
}

void ACWeapone::OnReload()
{
	MagEmtyComp->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("Mag_Hand"));
	MagEmtyComp->SetSimulatePhysics(true);
	MagEmtyComp->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
}

void ACWeapone::OffReload()
{
	MagEmtyComp->SetSimulatePhysics(false);
	MagEmtyComp->AttachToComponent(OwnerCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("Mag_Hand"));
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