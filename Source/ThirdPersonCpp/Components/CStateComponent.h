#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CStateComponent.generated.h"

UENUM(BlueprintType)
enum class EStateType: uint8
{
	Idle,Roll,Backstep
};

DECLARE_DYNAMIC_MULTICAST_DELEGTAE_TwoParams(FStateTypeChanged, EStateType, InPreType, EStateType, InNewType);

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
	FORCEINLINE boll IsIdleMode() {return Type == EStateType::Idle}
	UFUNCTION(BlueprintPure)
		FORCEINLINE boll IsRollMode() { return Type == EStateType::Roll }
	UFUNCTION(BlueprintPure)
		FORCEINLINE boll IsBackstepMode() { return Type == EStateType::Backstep }

	void SetIdleMode();
	void SetRollMode();
	void SetBackstepMode();

private:
	void ChahgeType(EStateType NewType);

public:
	UPROPERTY(BlueprintAssignable)
	FStateTypeChanged OnStateTypeChanged;

public:	
	EStateType Type;
		
};
