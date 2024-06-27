#include "CEnemy.h"
#include "Global.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/CAttributeComponent.h"
#include "Components/CMontagesComponent.h"
#include "Components/CActionComponent.h"

ACEnemy::ACEnemy()
{
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	GetMesh()->SetRelativeLocation(FVector(0, 0, -80));

	USkeletalMesh* MeshAsset;
	CHelpers::GetAsset<USkeletalMesh>(&MeshAsset, "/Game/Character/Mesh/SK_Mannequin");
	GetMesh()->SetSkeletalMesh(MeshAsset);


	//Create Actor Component
	CHelpers::CreateActorComponent(this, &ActionComp, "ActionComp");
	CHelpers::CreateActorComponent(this, &MontageComp, "MontageComp");
	CHelpers::CreateActorComponent(this, &AttributeComp, "AttributeComp");
	CHelpers::CreateActorComponent(this, &StateComp, "StateComp");

	TSubclassOf<UAnimInstance>AnimInstanceClass;
	CHelpers::GetClass<UAnimInstance>(&AnimInstanceClass, "/Game/Enemis/ABP_Enemy");
	GetMesh()->SetAnimInstanceClass(AnimInstanceClass);

	GetCharacterMovement()->MaxWalkSpeed = AttributeComp->GetSprintSpeed();
	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);

}

void ACEnemy::BeginPlay()
{

	//Create Material Dynamic
	{
		UMaterialInstanceConstant* BodyMaterialAsset;
		UMaterialInstanceConstant* LogoMaterialAsset;

		CHelpers::GetAssetDynamic(&BodyMaterialAsset, "/Game/Character/Materials/MI_UE4Man_Body");
		CHelpers::GetAssetDynamic(&LogoMaterialAsset, "/Game/Character/Materials/M_UE4Man_ChestLogo");

		BodyMaterial = UMaterialInstanceDynamic::Create(BodyMaterialAsset, this);
		LogoMaterial = UMaterialInstanceDynamic::Create(LogoMaterialAsset, this);

		GetMesh()->SetMaterial(0, BodyMaterial);
		GetMesh()->SetMaterial(1, LogoMaterial);
	}
	ActionComp->SetUnArmedMode();

	Super::BeginPlay();
}

void ACEnemy::ChangeBodyColor(FLinearColor InColor)
{
	BodyMaterial->SetVectorParameterValue("BodyColor", InColor);
	LogoMaterial->SetVectorParameterValue("BodyColor", InColor);
}


