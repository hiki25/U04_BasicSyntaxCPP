// Fill out your copyright notice in the Description page of Project Settings.


#include "CBoxBase_RedDoor.h"


void ACBoxBase_RedDoor::OpenTheDoor(float InRotator)
{
	if (Player->GetKey()->GetRedKey() > 0)
	{
		Player->GetKey()->UseRedKey();
		Door->SetRelativeRotation(FRotator(0, InRotator, 0));
		bDoorOpen = true;
	}
}
