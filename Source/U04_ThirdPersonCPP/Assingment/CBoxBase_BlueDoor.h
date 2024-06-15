// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Assingment/CBoxBase_Door.h"
#include "CBoxBase_BlueDoor.generated.h"



UCLASS()
class U04_THIRDPERSONCPP_API ACBoxBase_BlueDoor : public ACBoxBase_Door
{
	GENERATED_BODY()



public:
	virtual void OpenTheDoor(float InRotator) override;


	
};
