#include "CAnimNotifyState_UnEquip.h"
#include "CWeaponeInterface.h"
#include "CWeapone.h"

FString UCAnimNotifyState_UnEquip::GetNotifyName_Implementation() const
{
	return "UnEquip";
}

void UCAnimNotifyState_UnEquip::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	
	if(MeshComp->GetOwner() == nullptr) return;

	ICWeaponeInterface* ImplementedOwner = Cast<ICWeaponeInterface>(MeshComp->GetOwner());
	if (ImplementedOwner == nullptr) return;

	ACWeapone* Weapone = ImplementedOwner->GetWeapone();
	if (ImplementedOwner->GetWeapone() == nullptr) return;

	Weapone->Begin_UnEquip();

	
}

void UCAnimNotifyState_UnEquip::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if (MeshComp->GetOwner() == nullptr) return;

	ICWeaponeInterface* ImplementedOwner = Cast<ICWeaponeInterface>(MeshComp->GetOwner());
	if (ImplementedOwner == nullptr) return;

	ACWeapone* Weapone = ImplementedOwner->GetWeapone();
	if (Weapone == nullptr) return;

	Weapone->End_UnEquip();
}
