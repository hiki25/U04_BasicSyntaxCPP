// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CParticles.generated.h"

class UParticleSystem;
class ACBoxBase_Event;

UCLASS()
class U04_THIRDPERSONCPP_API ACParticles : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACParticles();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void SpawnEmitter(int32 InIndex);

private:
	UPROPERTY(EditAnywhere, Category = "Particle")
	UParticleSystem* Particles[3];

	UPROPERTY(EditAnywhere, Category = "HasEvent")
	ACBoxBase_Event* HasEventActor;


};
