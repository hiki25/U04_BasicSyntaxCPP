// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Assingment/CBoxBase_Door.h"
#include "CBoxBase_GreenDoor.generated.h"



UCLASS()
class U04_THIRDPERSONCPP_API ACBoxBase_GreenDoor : public ACBoxBase_Door
{

	GENERATED_BODY()

public:
		virtual void OpenTheDoor(float InRotator) override;


	
};
