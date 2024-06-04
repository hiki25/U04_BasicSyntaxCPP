// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CStaticMesh_Spawner.generated.h"

class ACStaticMeshBase;

UCLASS()
class U04_THIRDPERSONCPP_API ACStaticMesh_Spawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACStaticMesh_Spawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
protected:
	UPROPERTY(EditDefaultsOnly)
	UClass* WhatIsClassRef;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACStaticMeshBase> WhatIsTsubClassOf;
	
	UPROPERTY(EditDefaultsOnly, Category = " Spawn")
	TSubclassOf<ACStaticMeshBase> SpawnClasses[4];

private:
	ACStaticMeshBase* SpawnedObjects[4];

};
