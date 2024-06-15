#pragma once

#include "CoreMinimal.h"
#include "Assingment/CBoxBase_Door.h"
#include "CBoxBase_RedDoor.generated.h"

UCLASS()
class U04_THIRDPERSONCPP_API ACBoxBase_RedDoor : public ACBoxBase_Door
{
	GENERATED_BODY()

public:
		virtual void OpenTheDoor(float InRotator) override;
	
};
