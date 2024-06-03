
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CProperty.generated.h"

UCLASS()
class U04_THIRDPERSONCPP_API ACProperty : public AActor
{
	GENERATED_BODY()
	
public:	

	ACProperty();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnyWhere)
	int NumA;

	UPROPERTY(EditInstanceOnly)
	int NumB;

	UPROPERTY(EditDefaultsOnly)
	int NumC;

	UPROPERTY(VisibleAnyWhere)
		float RealA;

	UPROPERTY(VisibleInstanceOnly)
		float RealB;

	UPROPERTY(VisibleDefaultsOnly)
		float RealC;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float RealD = 3.14f;

};
