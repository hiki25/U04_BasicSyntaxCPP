#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Assingment/CBoxBase_Box.h"
#include "CPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class ACBoxBase_Box;

UCLASS()
class U04_THIRDPERSONCPP_API ACPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	ACPlayer();


protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);

	void OnSprint();
	void OffSprint();

	void OnOpen();
	void OffOpen();

public:
	bool bOpen = false;

private:
	UPROPERTY(VisibleAnywhere)
		USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere)
		UCameraComponent* CameraComp;

private:
};
