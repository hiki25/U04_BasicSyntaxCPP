#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CDelegate.generated.h"

DECLARE_DELEGATE_OneParam(FOpenDoor, float);

UCLASS()
class U04_THIRDPERSONCPP_API ACDelegate : public AActor
{
	GENERATED_BODY()
	
public:	
	ACDelegate();

protected:
	virtual void BeginPlay() override;



public:
	FOpenDoor OnOpenDoor;

};
