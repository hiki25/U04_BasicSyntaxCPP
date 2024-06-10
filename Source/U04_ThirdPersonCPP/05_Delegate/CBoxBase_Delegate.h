#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBoxBase.h"
#include "CBoxBase_Delegate.generated.h"

DECLARE_DELEGATE(FBoxBeginOverlap);
DECLARE_DELEGATE(FBoxEndOverlap);
DECLARE_DELEGATE_RetVal_OneParam(FString,FBoxOneParam,FLinearColor);

UCLASS()
class U04_THIRDPERSONCPP_API ACBoxBase_Delegate : public ACBoxBase
{
	GENERATED_BODY()

protected:
	virtual void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;
	virtual void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor) override;

public:
	FBoxBeginOverlap OnBoxBeginOverlap;
	FBoxEndOverlap OnBoxEndOverlap;
	FBoxOneParam OnBoxOneParam;
	
};
