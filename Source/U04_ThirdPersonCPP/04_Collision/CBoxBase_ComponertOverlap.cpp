#include "CBoxBase_ComponertOverlap.h"
#include "Components/PointLightComponent.h"
#include "Components/BoxComponent.h"

ACBoxBase_ComponertOverlap::ACBoxBase_ComponertOverlap()
{
	PointLightComp = CreateDefaultSubobject<UPointLightComponent>("PointLightComp");
	PointLightComp->SetupAttachment(RootComp);
	PointLightComp->SetLightColor(FLinearColor::Green);

}

void ACBoxBase_ComponertOverlap::BeginPlay()
{
	Super::BeginPlay();

	PointLightComp->SetVisibility(false);

	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ACBoxBase_ComponertOverlap::ComponentBeginOverlap);
	BoxComp->OnComponentEndOverlap.AddDynamic(this, &ACBoxBase_ComponertOverlap::ComponentEndOverlap);
}

void ACBoxBase_ComponertOverlap::ComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PointLightComp->SetVisibility(true);
}

void ACBoxBase_ComponertOverlap::ComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	PointLightComp->SetVisibility(false);
}
