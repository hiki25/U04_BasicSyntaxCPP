#include "CAnimInstance.h"
#include "CWeaponeInterface.h"
#include "CWeapone.h"
#include "Global.h"

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (OnwerPawn)
	{
		Speed = OnwerPawn->GetVelocity().Size2D();
		
		//�˻��Ҷ� Ŭ������ U
		//OnwerPawn->Implements<UCWeaponeInterface>()

		ICWeaponeInterface* ImplementedPawn = Cast<ICWeaponeInterface>(OnwerPawn);
		if (ImplementedPawn)
		{
			ACWeapone* Weapone = ImplementedPawn->GetWeapone();
			if (Weapone)
			{
				bEquipped = Weapone->IsEquipped();
			}
		}
	}
}

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	OnwerPawn = TryGetPawnOwner();
}
