#include "CKey.h"

ACKey::ACKey()
{
}

void ACKey::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACKey::GainRedKey()
{
	RedKey++;
}

void ACKey::GainBlueKey()
{
	BlueKey++;
}

void ACKey::GainGreenKey()
{
	GreenKey++;
}

void ACKey::UseGreenKey()
{
	GreenKey--;
}

void ACKey::UseBlueKey()
{
	BlueKey--;
}

void ACKey::UseRedKey()
{
	RedKey--;
}


