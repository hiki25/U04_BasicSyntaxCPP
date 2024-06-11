// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "04_Collision/CBoxBase.h"
#include "CBoxBase_ActorOverlap.generated.h"

/**
 * 
 */
UCLASS()
class U04_THIRDPERSONCPP_API ACBoxBase_ActorOverlap : public ACBoxBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	void ActorBeginOverlap(AActor* OverlapedActor, AActor* OtherActor) override;
	
};