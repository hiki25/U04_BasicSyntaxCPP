// Fill out your copyright notice in the Description page of Project Settings.


#include "CBoxBase_BlueDoor.h"
#include "CKey.h"
#include "../CPlayer.h"


void ACBoxBase_BlueDoor::OpenTheDoor(float InRotator)
{
	Super::OpenTheDoor(InRotator);
	if (Player->GetKey()->GetBlueKey() > 0)
	{
		Player->GetKey()->UseBlueKey();
		Door->SetRelativeRotation(FRotator(0, InRotator, 0));
		bDoorOpen = true;
	}
}
