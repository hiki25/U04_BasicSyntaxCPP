#pragma once

#include "CoreMinimal.h"
#include "Assingment/CBoxBase_Box.h"
#include "CBoxBase_BlueBox.generated.h"



UCLASS()
class U04_THIRDPERSONCPP_API ACBoxBase_BlueBox : public ACBoxBase_Box
{
	GENERATED_BODY()
public:
	ACBoxBase_BlueBox();
private:

	virtual void OpenTheDoor(float InRotator) override;


	
};
