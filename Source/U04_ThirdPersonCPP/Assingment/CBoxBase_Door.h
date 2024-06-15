#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBoxBase.h"
#include "CPlayer.h"
#include "CKey.h"
#include "CBoxBase_Door.generated.h"

class ACPlayer;

UCLASS()
class U04_THIRDPERSONCPP_API ACBoxBase_Door : public ACBoxBase
{
	GENERATED_BODY()

public:
	ACBoxBase_Door();
	
private:

	virtual void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;
	virtual void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor) override;

	virtual void OnConstruction(const FTransform& Transform) override;

	virtual void BeginPlay() override;

public:
	UFUNCTION()
	virtual void OpenTheDoor(float InRotator);

protected:
	bool bDoorOpen = false;

protected:
	UPROPERTY(VisibleAnyWhere)
	UStaticMeshComponent* Door;


private:
	UPROPERTY(VisibleAnyWhere)
	UStaticMeshComponent* DoorFrame;

	UPROPERTY(EditAnywhere, Category = "DoorColor")
	FLinearColor MaterialColor;

	UMaterialInstanceDynamic* DynamicMaterial;

protected:
	ACPlayer* Player;

	
};
