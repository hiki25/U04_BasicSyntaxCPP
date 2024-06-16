#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBoxBase.h"
#include "CBoxBase_Door.generated.h"

class UStaticMeshComponent;
class ACPlayer;
class UMaterialInstanceDynamic;

UCLASS()
class U04_THIRDPERSONCPP_API ACBoxBase_Door : public ACBoxBase
{
	GENERATED_BODY()
	
public:
	ACBoxBase_Door();
	UPROPERTY(EditInstanceOnly, Category = "MaterialColor")
		FLinearColor DoorColor;
	UPROPERTY(EditInstanceOnly, Category = "Key")
		FName Key;

public:
	UFUNCTION()
		void OpenTheDoor(float InRotator);
	FName GetName() { return Key; }

protected:
	virtual void BeginPlay() override;

private:
	virtual void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;
	virtual void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor) override;
	virtual void OnConstruction(const FTransform& Transform) override;

private:
	UPROPERTY(VisibleAnyWhere)
		UStaticMeshComponent* Door;
	UPROPERTY(VisibleAnyWhere)
		UStaticMeshComponent* DoorFrame;
	ACPlayer* Player;
	UMaterialInstanceDynamic* DoorDynamicMaterial;
	UMaterialInstanceDynamic* FrameDynamicMaterial;
	bool bOpen = false;
};
