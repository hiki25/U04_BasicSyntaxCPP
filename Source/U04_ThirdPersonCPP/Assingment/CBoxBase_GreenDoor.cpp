// Fill out your copyright notice in the Description page of Project Settings.


#include "CBoxBase_GreenDoor.h"




void ACBoxBase_GreenDoor::OpenTheDoor(float InRotator)
{
	Super::OpenTheDoor(InRotator);
	if (Player->GetKey()->GetGreenKey() > 0)
	{
		Player->GetKey()->UseGreenKey();
		Door->SetRelativeRotation(FRotator(0, InRotator, 0));
		bDoorOpen = true;
	}
}
