#include "CBoxBase_RedBox.h"
#include "Global.h"

ACBoxBase_RedBox::ACBoxBase_RedBox()
{
	
}

void ACBoxBase_RedBox::OpenTheDoor(float InRotator)
{
	Super::OpenTheDoor(InRotator);
	if (bOpen == false)
	{
		Player->GetKey()->GainRedKey();
	}
	bOpen = true;
}