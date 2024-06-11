#include "CSpotLight.h"
#include "Global.h"
#include "Components/SpotLightComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "CBoxBase_MultiCast.h"

ACSpotLight::ACSpotLight()
{
	RootComp = CreateDefaultSubobject<USceneComponent>("RootComp");
	RootComponent = RootComp;

	for (int32 i = 0; i < 3; i++)
	{
		FString Str;
		Str.Append("SpotLightComp");
		Str.Append(FString::FromInt(i + 1));


		SpotLightComp[i] = CreateDefaultSubobject<USpotLightComponent>(FName(Str));
		SpotLightComp[i]->SetupAttachment(RootComp);
		SpotLightComp[i]->SetRelativeLocation(FVector(0, i * 150, 0));
		SpotLightComp[i]->SetRelativeRotation(FRotator(-90,0, 0));

		SpotLightComp[i]->Intensity = 1e+5f;
		SpotLightComp[i]->OuterConeAngle = 25.f;


	}
}

void ACSpotLight::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACBoxBase_MultiCast::StaticClass(), actors);
	if (actors.Num() < 1)
	{
		return;
	}

	ACBoxBase_MultiCast* Tirgger = Cast<ACBoxBase_MultiCast>(actors[0]);
	Tirgger->OnMulticastBeginOverlap.AddUObject(this, &ACSpotLight::OnLight);
}

void ACSpotLight::OnLight(int32 InIndex, FLinearColor InColor)
{
	for (int32 i = 0; i < 3; i++)
	{
		SpotLightComp[i]->SetLightColor(FLinearColor::White);
	}
	SpotLightComp[InIndex]->SetLightColor(InColor);
}


