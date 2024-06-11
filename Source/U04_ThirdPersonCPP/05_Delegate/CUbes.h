#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CUbes.generated.h"

class UStaticMeshComponent;

UCLASS()
class U04_THIRDPERSONCPP_API ACUbes : public AActor
{
	GENERATED_BODY()
	
public:	
	ACUbes();

protected:
	virtual void BeginPlay() override;

private:
	void Drop(int32 InIndex, FLinearColor InColor);

private:
	UPROPERTY(VisibleDefaultsOnly)
	USceneComponent* RootComp;

	UPROPERTY(VisibleDefaultsOnly)
	UStaticMeshComponent* MeshComp[3];

private:
	UMaterialInstanceDynamic* DynamicMaterial[3];
	FVector OriginLocation[3];
	FQuat OriginRotation[3];
};
