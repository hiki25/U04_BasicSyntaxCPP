#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CActionData.generated.h"

class UAnimMontage;
class ACEquipment;
class ACharacter;
class ACAttachment;
class UParticleSystem;
class UCameraShake;
class ACDoAction;

USTRUCT(BlueprintType)
struct FEquipmentData
{
	GENERATED_BODY()



public:
	UPROPERTY(EditDefaultsOnly)
		UAnimMontage* AnimMontage;

	UPROPERTY(EditDefaultsOnly)
		float PlayRate = 1.f;

	UPROPERTY(EditDefaultsOnly)
		FName StartSection;

	UPROPERTY(EditDefaultsOnly)
		bool bCanMove = true;

	UPROPERTY(EditDefaultsOnly)
		bool bLookForward = true;
};

USTRUCT(BlueprintType)
struct FDoActionData :public FEquipmentData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly)
		float Power = 1.f;

	UPROPERTY(EditDefaultsOnly)
		float HitStop;

	UPROPERTY(EditDefaultsOnly)
		UParticleSystem* Effect;

	UPROPERTY(EditDefaultsOnly)
		FTransform EffectTransform;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UCameraShake> ShakeClass;

};

UCLASS()
class THIRDPERSONCPP_API UCActionData : public UDataAsset
{
	GENERATED_BODY()

public:
	void BeginPlay(ACharacter* InOnwerCharacter);

private:
	FString MakeActorLable(ACharacter* InOwnerCharacter, FString InMiddleName);

public:
	FORCEINLINE ACEquipment* GetEquipment() { return Equipment; }
	FORCEINLINE ACAttachment* GetAttachment() { return Attachment; }
	FORCEINLINE ACDoAction* GetDoAction() { return DoAction; }

public:
	UPROPERTY(EditAnywhere, Category = "Equipment")
	TSubclassOf<ACEquipment> EquipmentClass;

	UPROPERTY(EditAnywhere, Category = "Equipment")
	FEquipmentData EquipmentData;

	UPROPERTY(EditAnywhere, Category = "Equipment")
		FLinearColor EquipmentColor;

	UPROPERTY(EditAnywhere, Category = "Attachment")
	TSubclassOf<ACAttachment> AttachmentClass;

	UPROPERTY(EditAnywhere, Category = "DoAction")
	TSubclassOf<ACDoAction> DoActionClass;

	UPROPERTY(EditAnywhere, Category = "DoAction")
	TArray<FDoActionData> DoActinoDatas;

private:
	ACEquipment* Equipment;
	ACAttachment* Attachment;
	ACDoAction* DoAction;
	
};
