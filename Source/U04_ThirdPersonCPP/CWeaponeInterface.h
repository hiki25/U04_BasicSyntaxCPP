#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CWeaponeInterface.generated.h"

class ACWeapone;

UINTERFACE(MinimalAPI) //에디터에 전송, 건들면 안됨
class UCWeaponeInterface : public UInterface
{
	GENERATED_BODY()
};

//순수가상함수 정의
class U04_THIRDPERSONCPP_API ICWeaponeInterface
{
	GENERATED_BODY()

public:
	virtual ACWeapone* GetWeapone() = 0;
	virtual void GetAimInfo(FVector& OutAimStart, FVector& OutAimEnd, FVector& OutAimDirection) = 0;

	virtual void OnTarget() {}
	virtual void OffTarget() {}
};
