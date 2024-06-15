#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBoxBase.h"
#include "CPlayer.h"
#include "CBoxBase_Box.generated.h"


class UMaterialInstanceDynamic;

UCLASS()
class U04_THIRDPERSONCPP_API ACBoxBase_Box : public ACBoxBase
{
	GENERATED_BODY()

public:
	ACBoxBase_Box();

public:
	UPROPERTY(EditDefaultsOnly)
		FLinearColor ChestColor;
	
private:

	virtual void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;
	virtual void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor) override;


	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	UFUNCTION()
	 virtual void OpenTheDoor(float InRotator); 
	ACPlayer* Player;

private:
	UPROPERTY(VisibleAnyWhere)
	UStaticMeshComponent* ChestBottom;
	UPROPERTY(VisibleAnyWhere)
	UStaticMeshComponent* ChestTop;

	

	UMaterialInstanceDynamic* ChestMaterialDynamic;

	
};
