#include "CBoxBase_GreenBox.h"
#include "Global.h"

ACBoxBase_GreenBox::ACBoxBase_GreenBox()
{
	
}

void ACBoxBase_GreenBox::OpenTheDoor(float InRotator)
{
	Super::OpenTheDoor(InRotator);
	if (bOpen == false)
	{
		Player->GetKey()->GainGreenKey();
	}
	bOpen = true;
}
