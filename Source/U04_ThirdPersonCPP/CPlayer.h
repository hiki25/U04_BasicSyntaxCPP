#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Assingment/CBoxBase_Box.h"
#include "CPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class ACBoxBase_Box;
class ACBoxBase_Door;
class ACKey;

UCLASS()
class U04_THIRDPERSONCPP_API ACPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	ACPlayer();

private:
	virtual void Tick(float DeltaSeconds) override;
	float DeltaTime = 0.0f;

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);

	void OnSprint();
	void OffSprint();

	void OnOpen();

public:

public:
	UFUNCTION()
	void ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);
	UFUNCTION()
	void ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor);


private:
	UPROPERTY(VisibleAnywhere)
		USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
		UCameraComponent* CameraComp;



private:
	ACBoxBase_Box* Box = nullptr;
	ACBoxBase_Door* Door = nullptr;

	TArray<FName> Key;
};
