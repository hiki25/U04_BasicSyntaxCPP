#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStateComponent.generated.h"

UENUM(BlueprintType)
enum class EStateType: uint8
{
	Idle,Roll,Backstep,Equip,Max
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStateTypeChanged, EStateType, InPreType, EStateType, InNewType);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THIRDPERSONCPP_API UCStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCStateComponent();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsIdleMode() { return Type == EStateType::Idle; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsRollMode() { return Type == EStateType::Roll; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsBackstepMode() { return Type == EStateType::Backstep; }
	UFUNCTION(BlueprintPure)
		FORCEINLINE bool IsEquipMode() { return Type == EStateType::Equip; }

	void SetIdleMode();
	void SetRollMode();
	void SetBackstepMode();
	void SetEquipMode();

private:
	void ChahgeType(EStateType NewType);

public:
	UPROPERTY(BlueprintAssignable)
	FStateTypeChanged OnStateTypeChanged;

public:	
	EStateType Type;
		
};
