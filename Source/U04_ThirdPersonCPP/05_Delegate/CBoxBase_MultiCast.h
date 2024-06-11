// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBoxBase.h"
#include "CBoxBase_MultiCast.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FMulticastBeginOverlap, int32, FLinearColor);

UCLASS()
class U04_THIRDPERSONCPP_API ACBoxBase_MultiCast : public ACBoxBase
{
	GENERATED_BODY()

protected:
	virtual void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor) override;

public:
	FMulticastBeginOverlap OnMulticastBeginOverlap;

	
};
