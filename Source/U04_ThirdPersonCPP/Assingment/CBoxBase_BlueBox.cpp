#include "CBoxBase_BlueBox.h"
#include "Global.h"

ACBoxBase_BlueBox::ACBoxBase_BlueBox()
{
	
}

void ACBoxBase_BlueBox::OpenTheDoor(float InRotator)
{
	Super::OpenTheDoor(InRotator);
	if (bOpen == false)
	{
		Player->GetKey()->GainBlueKey();
	}
	bOpen = true;
}