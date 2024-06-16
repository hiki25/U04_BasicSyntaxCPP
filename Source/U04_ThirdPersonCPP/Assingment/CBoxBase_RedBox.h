#pragma once

#include "CoreMinimal.h"
#include "Assingment/CBoxBase_Box.h"
#include "CBoxBase_RedBox.generated.h"


UCLASS()
class U04_THIRDPERSONCPP_API ACBoxBase_RedBox : public ACBoxBase_Box
{
	GENERATED_BODY()


public:
	ACBoxBase_RedBox();
private:
	virtual void OpenTheDoor(float InRotator) override;

	
};
