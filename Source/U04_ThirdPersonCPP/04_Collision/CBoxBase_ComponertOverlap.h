#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBoxBase.h"
#include "CBoxBase_ComponertOverlap.generated.h"

class UPointLightComponent;
UCLASS()
class U04_THIRDPERSONCPP_API ACBoxBase_ComponertOverlap : public ACBoxBase
{
	GENERATED_BODY()

public:
	ACBoxBase_ComponertOverlap();

protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(VisibleDefaultsOnly)
	UPointLightComponent* PointLightComp;

private:
	UFUNCTION()
	void ComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void ComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	
};
