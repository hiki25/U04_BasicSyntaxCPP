#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CAutoWidget.generated.h"


UCLASS()
class U04_THIRDPERSONCPP_API UCAutoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
		UFUNCTION(BlueprintImplementableEvent)
		void OnAuto();

	UFUNCTION(BlueprintImplementableEvent)
		void OffAuto();

	UFUNCTION(BlueprintImplementableEvent)
		void BulletCount(int32 Max, int32 Current);
};
