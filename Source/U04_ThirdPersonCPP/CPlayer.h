#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CWeaponeInterface.h"
#include "CPlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UMaterialInstanceDynamic;
class ACWeapone;
class UCCrossHairWidget;
class UCAutoWidget;



UCLASS()
class U04_THIRDPERSONCPP_API ACPlayer : public ACharacter, public ICWeaponeInterface
{
	GENERATED_BODY()

public:
	ACPlayer();

	UFUNCTION(Exec)
	void ChangeSpeed(float InMoveSpeed = 400.f);

	FORCEINLINE ACWeapone* GetWeapone() override { return Weapone; }

	void Reload();



protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void OnTarget() override;
	virtual void OffTarget() override;

private:
	void OnMoveForward(float Axis);
	void OnMoveRight(float Axis);

	void OnSprint();
	void OffSprint();

	void ToggleEquip();
	void ToggleAuto();

	void OnAim();
	void OffAim();

	void OnFire();
	void OffFire();


public:
	UFUNCTION(BlueprintCallable)
	void SetBodyColor(FLinearColor InBodyColor, FLinearColor InLogoColor);

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void Begin_Zoom();

	UFUNCTION(BlueprintImplementableEvent)
	void End_Zoom();

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
		UCameraComponent* CameraComp;

private:
	UPROPERTY(VisibleAnywhere)
		USpringArmComponent* SpringArmComp;


	UPROPERTY(EditDefaultsOnly, Category = "WeaponClass")
	TSubclassOf<ACWeapone> WeaponeClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgetclass")
	TSubclassOf<UCCrossHairWidget> CrossHairWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgetclass")
	TSubclassOf<UCAutoWidget> AutoWidgetClass;

public:
	UFUNCTION()
		void CallCountBullet(int32 CurrentBullet,int32 MaxBullet);
private:
	UMaterialInstanceDynamic* BodyMaterial;
	UMaterialInstanceDynamic* LogoMaterial;

	ACWeapone* Weapone;
	UCCrossHairWidget* CrossHairWidget;
	UCAutoWidget* AutoWidget;


	// Inherited via ICWeaponeInterface
	virtual void GetAimInfo(FVector& OutAimStart, FVector& OutAimEnd, FVector& OutAimDirection) override;

	
};
