// Fill out your copyright notice in the Description page of Project Settings.


#include "CBoxBase_Event.h"
#include "Global.h"

void ACBoxBase_Event::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OnEventBeginOverlap.IsBound())
	{
		OnEventBeginOverlap.Broadcast(UKismetMathLibrary::RandomIntegerInRange(0, 2));
	}
}
