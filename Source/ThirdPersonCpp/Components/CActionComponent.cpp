#include "CActionComponent.h"

UCActionComponent::UCActionComponent()
{

}


void UCActionComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UCActionComponent::SetUnArmedMode()
{
}

void UCActionComponent::SetOneHandMode()
{
}

void UCActionComponent::SetTwoHandMode()
{
}

void UCActionComponent::SetMagicBallMode()
{
}

void UCActionComponent::SetWarpMode()
{
}

void UCActionComponent::SetWhirlWindMode()
{
}

void UCActionComponent::SetMode(EActionType InNewType)
{
}

void UCActionComponent::ChangeType(EActionType InNewType)
{
	EActionType Prev = Type;
	Type = InNewType;

	if (OnActionTypeChanged.IsBound())
	{
		OnActionTypeChanged.BroadCast(Prev, InNewType);
	}
}
