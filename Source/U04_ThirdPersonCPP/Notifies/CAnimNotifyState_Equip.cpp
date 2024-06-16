#include "CAnimNotifyState_Equip.h"
#include "CWeaponeInterface.h"
#include "CWeapone.h"

FString UCAnimNotifyState_Equip::GetNotifyName_Implementation() const
{
	return "Equip";
}

void UCAnimNotifyState_Equip::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	
	if(MeshComp->GetOwner() == nullptr) return;

	ICWeaponeInterface* ImplementedOwner = Cast<ICWeaponeInterface>(MeshComp->GetOwner());
	if (ImplementedOwner == nullptr) return;

	ACWeapone* Weapone = ImplementedOwner->GetWeapone();
	if (ImplementedOwner->GetWeapone() == nullptr) return;

	Weapone->Begin_Equip();

	
}

void UCAnimNotifyState_Equip::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if (MeshComp->GetOwner() == nullptr) return;

	ICWeaponeInterface* ImplementedOwner = Cast<ICWeaponeInterface>(MeshComp->GetOwner());
	if (ImplementedOwner == nullptr) return;

	ACWeapone* Weapone = ImplementedOwner->GetWeapone();
	if (Weapone == nullptr) return;

	Weapone->End_Equip();
}
