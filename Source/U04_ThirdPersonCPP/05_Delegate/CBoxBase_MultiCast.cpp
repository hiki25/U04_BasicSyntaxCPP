#include "Global.h"

#include "CBoxBase_MultiCast.h"

void ACBoxBase_MultiCast::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Super::ActorBeginOverlap(OverlappedActor, OtherActor);

	if (OnMulticastBeginOverlap.IsBound())
	{
		int32 RandomIndex = UKismetMathLibrary::RandomIntegerInRange(0,2);
		FLinearColor RandomColor = FLinearColor::MakeRandomColor();	

		OnMulticastBeginOverlap.Broadcast(RandomIndex, RandomColor);
	}
}