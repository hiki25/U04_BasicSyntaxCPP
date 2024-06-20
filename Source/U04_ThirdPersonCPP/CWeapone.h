#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CWeapone.generated.h"

class USkeletalMeshComponent;
class ACharacter;
class UAnimMontage;
class ACBullet;
class UParticleSystem;
class USoundCue;
class UDecalComponent;
class UMaterialInstanceConstant;

UCLASS()
class U04_THIRDPERSONCPP_API ACWeapone : public AActor
{
	GENERATED_BODY()
	
public:	
	ACWeapone();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	FORCEINLINE bool IsEquipped() { return bEquipped; }
	FORCEINLINE bool IsEquipping() { return bEquipping; }
	FORCEINLINE bool IsReloading() { return bReloading; }
	FORCEINLINE bool IsAiming() { return bAiming; }
	FORCEINLINE bool IsFiring() { return bFring; }
	FORCEINLINE bool IsAutoFire() { return bAutoFire; }
	FORCEINLINE int32 GetCurrentBullet() { return CurrentBullet; }
	FORCEINLINE int32 GetMaxBullet() { return MaxBullet; }
	FORCEINLINE USkeletalMeshComponent* GetMesh() { return MeshComp; }

	void BeginAiming();
	void EndAiming();
	//Get은 인라인 함수로 만드는데 Set함수는 만들지 않는다
	//유지 보수 편하게 하기 위해

	void Equip();
	void UnEquip();
	void RelaodBullet();

	void Begin_Reload();
	void End_Reload();
	void Begin_Equip();
	void End_Equip();
	void Begin_UnEquip();
	void End_UnEquip();
	void Begin_Fire();
	void End_Fire();

	void ToggleAutoFire();

	

	void OnFire();
	void OnReload();
	void OffReload();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
	TSubclassOf<ACBullet> Bulletclass;

	UPROPERTY(EditDefaultsOnly, Category = "Bullet")
		int32 MaxBullet;

	UPROPERTY(EditDefaultsOnly, Category = "BulletParticle")
	UParticleSystem* FireParticle;

	UPROPERTY(EditDefaultsOnly, Category = "BulletParticle")
	UParticleSystem* EjectParticle;

	UPROPERTY(EditDefaultsOnly, Category = "BulletSound")
	USoundCue* FireSound;

	UPROPERTY(EditDefaultsOnly, Category = "ImpactParticle")
		UParticleSystem* ImpactParticle;

	UPROPERTY(EditDefaultsOnly, Category = "Decal")
	UMaterialInstanceConstant* Decal;

	UPROPERTY(EditDefaultsOnly, Category = "Soket")
	FName HolsterSoket;

	UPROPERTY(EditDefaultsOnly, Category = "Soket")
	FName HandSoket;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* EquipMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* UnEquipMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* ReloadMontage;

	UPROPERTY(EditDefaultsOnly, Category = "CameraShake")
	TSubclassOf<UCameraShake> CameraShakeClass;


	UPROPERTY(EditDefaultsOnly, Category = "AutoFire")
	float FireInterval;
	UPROPERTY(EditDefaultsOnly, Category = "AutoFire")
		float PitchSpeed;

	

private:
	UPROPERTY(VisibleDefaultsOnly)
	USkeletalMeshComponent* MeshComp;

	UStaticMeshComponent* MagEmtyComp;
	
private:
	ACharacter* OwnerCharacter;

	FTimerHandle AutoTimerHandel;

	bool bEquipped;
	bool bEquipping;
	bool bReloading;
	bool bAiming;
	bool bFring;
	bool bAutoFire;
	float CurrentPitch;
	int32 CurrentBullet;

};
