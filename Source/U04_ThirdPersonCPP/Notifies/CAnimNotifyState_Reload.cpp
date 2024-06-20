#include "CAnimNotifyState_Reload.h"
#include "CWeaponeInterface.h"
#include "CWeapone.h"

FString UCAnimNotifyState_Reload::GetNotifyName_Implementation() const
{
	return "Reload";
}

void UCAnimNotifyState_Reload::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	
	if(MeshComp->GetOwner() == nullptr) return;

	ICWeaponeInterface* ImplementedOwner = Cast<ICWeaponeInterface>(MeshComp->GetOwner());
	if (ImplementedOwner == nullptr) return;

	ACWeapone* Weapone = ImplementedOwner->GetWeapone();
	if (ImplementedOwner->GetWeapone() == nullptr) return;

	Weapone->Begin_Reload();

	
}

void UCAnimNotifyState_Reload::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if (MeshComp->GetOwner() == nullptr) return;

	ICWeaponeInterface* ImplementedOwner = Cast<ICWeaponeInterface>(MeshComp->GetOwner());
	if (ImplementedOwner == nullptr) return;

	ACWeapone* Weapone = ImplementedOwner->GetWeapone();
	if (Weapone == nullptr) return;

	Weapone->End_Reload();
}
