#include "CStateComponent.h"

UCStateComponent::UCStateComponent()
{

}


void UCStateComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UCStateComponent::SetIdleMode()
{
	ChahgeType(EStateType::Idle);
}

void UCStateComponent::SetRollMode()
{
	ChahgeType(EStateType::Roll);
}

void UCStateComponent::SetBackstepMode()
{
	ChahgeType(EStateType::Backstep);
}

void UCStateComponent::ChahgeType(EStateType NewType)
{
	if (OnStateTypeChanged.IsBound())
	{
		EStateType Prev = Type;
		Type = NewType;

		OnStateTypeChanged.
	}
}



