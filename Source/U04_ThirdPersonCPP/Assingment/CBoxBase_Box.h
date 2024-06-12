#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBoxBase.h"
#include "CBoxBase_Box.generated.h"


UCLASS()
class U04_THIRDPERSONCPP_API ACBoxBase_Box : public ACBoxBase
{
	GENERATED_BODY()

public:
	ACBoxBase_Box();
	
private:

	virtual void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;

private:
	UFUNCTION()
	 void OpenTheDoor(float InRotator);

private:
	UPROPERTY(VisibleAnyWhere)
	UStaticMeshComponent* ChestBottom;
	UPROPERTY(VisibleAnyWhere)
	UStaticMeshComponent* ChestTop;

	
};
