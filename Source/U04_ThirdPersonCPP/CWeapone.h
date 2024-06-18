#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CWeapone.generated.h"

class USkeletalMeshComponent;
class ACharacter;
class UAnimMontage;

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
	FORCEINLINE bool IsAiming() { return bAiming; }
	FORCEINLINE USkeletalMeshComponent* GetMesh() { return MeshComp; }

	void BeginAiming();
	void EndAiming();

	void Begin_Fire();
	void End_Fire();

	UFUNCTION()
	void Firing();

	//Get은 인라인 함수로 만드는데 Set함수는 만들지 않는다
	//유지 보수 편하게 하기 위해

	void Equip();
	void UnEquip();

	void Begin_Equip();
	void End_Equip();
	void Begin_UnEquip();
	void End_UnEquip();

	

private:
	UPROPERTY(EditDefaultsOnly, Category = "Soket")
	FName HolsterSoket;

	UPROPERTY(EditDefaultsOnly, Category = "Soket")
	FName HandSoket;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* EquipMontage;

	UPROPERTY(EditDefaultsOnly, Category = "Montages")
	UAnimMontage* UnEquipMontage;

	UPROPERTY(EditDefaultsOnly, Category = "CameraShake")
	TSubclassOf<UCameraShake> CameraShakeClass;

private:
	UPROPERTY(VisibleDefaultsOnly)
	USkeletalMeshComponent* MeshComp;

private:
	ACharacter* OwnerCharacter;

	bool bEquipped;
	bool bEquipping;
	bool bAiming;
	bool bFiring;
};
