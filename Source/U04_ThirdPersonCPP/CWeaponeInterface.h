#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CWeaponeInterface.generated.h"

class ACWeapone;

UINTERFACE(MinimalAPI) //�����Ϳ� ����, �ǵ�� �ȵ�
class UCWeaponeInterface : public UInterface
{
	GENERATED_BODY()
};

//���������Լ� ����
class U04_THIRDPERSONCPP_API ICWeaponeInterface
{
	GENERATED_BODY()

public:
	virtual ACWeapone* GetWeapone() = 0;
};
