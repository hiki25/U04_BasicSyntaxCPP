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

protected:
	virtual void BeginPlay() override;

public:
	void GainRedKey();
	void GainBlueKey();
	void GainGreenKey();
	void UseGreenKey();
	void UseBlueKey();
	void UseRedKey();
	int32 GetRedKey() { return RedKey; }
	int32 GetGreenKey() {return GreenKey; }
	int32 GetBlueKey() { return BlueKey; }

private:
	int32 RedKey = 0;
	int32 GreenKey = 0;
	int32 BlueKey = 0;

};
