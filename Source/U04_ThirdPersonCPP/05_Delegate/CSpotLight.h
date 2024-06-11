#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSpotLight.generated.h"

class USpotLightComponent;

UCLASS()
class U04_THIRDPERSONCPP_API ACSpotLight : public AActor
{
	GENERATED_BODY()
	
public:	
	ACSpotLight();

protected:
	virtual void BeginPlay() override;

private:
	void OnLight(int32 InIndex, FLinearColor InColor);

private:
	UPROPERTY(VisibleDefaultsOnly)
	USceneComponent* RootComp;

	UPROPERTY(VisibleDefaultsOnly)
	USpotLightComponent* SpotLightComp[3];


};
