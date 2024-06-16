#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBoxBase.h"
#include "CBoxBase_Box.generated.h"

class ACPlayer;
class UMaterialInstanceDynamic;

UCLASS()
class U04_THIRDPERSONCPP_API ACBoxBase_Box : public ACBoxBase
{
	GENERATED_BODY()

public:
	ACBoxBase_Box();

	UPROPERTY(EditInstanceOnly, Category = "MaterialColor")
	FLinearColor ChestColor;
	UPROPERTY(EditInstanceOnly, Category = "Key")
	FName Key;

	UFUNCTION(BlueprintImplementableEvent, Category = "OpenBox")
		void OnOpenBox();

private:
	virtual void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;
	virtual void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor) override;
	virtual void OnConstruction(const FTransform& Transform) override;

public:
	UFUNCTION()
	 void OpenTheDoor(float InRotator);
	FName GetName() { return Key; }
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		UStaticMeshComponent* ChestBottom;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		UStaticMeshComponent* ChestTop;

private:
	
	ACPlayer* Player;
	UMaterialInstanceDynamic* DynamicMaterial;
	bool bOpen = false;
	
};
