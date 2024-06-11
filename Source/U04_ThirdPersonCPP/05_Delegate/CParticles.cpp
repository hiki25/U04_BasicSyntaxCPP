#include "CParticles.h"
#include "CBoxBase_Event.h"
#include "Global.h"

// Sets default values
ACParticles::ACParticles()
{

}

// Called when the game starts or when spawned
void ACParticles::BeginPlay()
{
	Super::BeginPlay();
	
	if (ensure(HasEventActor))
	{
		HasEventActor->OnEventBeginOverlap.AddUFunction(this, "SpawnEmitter");
	}
}

void ACParticles::SpawnEmitter(int32 InIndex)
{
	CLog::Print("Index : " + FString::FromInt(InIndex));
	if (ensure(InIndex))
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particles[InIndex], GetActorLocation());
	}
}


