#pragma once

#include "CoreMinimal.h"
#include "Assingment/CBoxBase_Box.h"
#include "CBoxBase_GreenBox.generated.h"



UCLASS()
class U04_THIRDPERSONCPP_API ACBoxBase_GreenBox : public ACBoxBase_Box
{
	GENERATED_BODY()
		
public:
	ACBoxBase_GreenBox();
private:
	virtual void OpenTheDoor(float InRotator) override;

private:

	
};
