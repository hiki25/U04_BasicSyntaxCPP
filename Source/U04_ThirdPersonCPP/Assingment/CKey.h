#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CKey.generated.h"

UCLASS()
class U04_THIRDPERSONCPP_API ACKey : public AActor
{
	GENERATED_BODY()
	
public:	
	ACKey();

	void SetColorKey(FLinearColor KeyColor);
protected:
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditInstanceOnly, Category = "MaterialColor")
	FLinearColor ColorKey = FLinearColor::Black;

public:
	FORCEINLINE FLinearColor GetKey() { return ColorKey; }
};
