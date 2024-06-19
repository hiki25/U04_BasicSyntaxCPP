// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CWeaponeWidget.generated.h"

/**
 * 
 */
UCLASS()
class U04_THIRDPERSONCPP_API UCWeaponeWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
		void OnAutoFire();

	UFUNCTION(BlueprintImplementableEvent)
		void OffAutoFire();

};
