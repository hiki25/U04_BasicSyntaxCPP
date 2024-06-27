#include "CDoAction_Melee.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CAttributeComponent.h"


void ACDoAction_Melee::DoAction()
{
	Super::DoAction();

	CheckFalse(Datas.Num() > 0);
	CheckFalse(StateComponent->IsIdleMode());

	StateComponent->SetActionMode();
	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage,Datas[0].PlayRate,Datas[0].StartSection);

	Datas[0].bCanMove ? AttributeComponent->SetMove() : AttributeComponent->SetStop();
}

void ACDoAction_Melee::Begin_DoAction()
{
	Super::Begin_DoAction();
}

void ACDoAction_Melee::End_DoAction()
{
	Super::End_DoAction();

	StateComponent->SetIdleMode();
	AttributeComponent->SetMove();
}