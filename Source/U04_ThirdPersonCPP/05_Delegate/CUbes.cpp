#include "CUbes.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "CBoxBase_MultiCast.h"

ACUbes::ACUbes()
{
	RootComp = CreateDefaultSubobject<USceneComponent>("RootComp");
	RootComponent = RootComp;

	ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset(TEXT("/Game/StaticMeshes/SM_Cube"));

	for (int32 i = 0; i < 3; i++)
	{
		FString Str;
		Str.Append("MeshComp");
		Str.Append(FString::FromInt(i + 1));
		MeshComp[i] = CreateDefaultSubobject<UStaticMeshComponent>(FName(Str));
		MeshComp[i]->SetupAttachment(RootComp);

		MeshComp[i]->SetRelativeLocation(FVector(0, i * 150, 0));
		MeshComp[i]->SetSimulatePhysics(false);

		if (MeshAsset.Succeeded())
		{
			MeshComp[i]->SetStaticMesh(MeshAsset.Object);
		}

	}
}

void ACUbes::BeginPlay()
{
	Super::BeginPlay();

	UObject* ContentAsset = StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("/Game/Materials/MI_StaticMesh_Inst"));
	UMaterialInstanceConstant* MaterialAsset = Cast<UMaterialInstanceConstant>(ContentAsset);

	for (int32 i = 0; i < 3; i++)
	{
		if (MaterialAsset)
		{
			DynamicMaterial[i] = UMaterialInstanceDynamic::Create(MaterialAsset, nullptr);
			MeshComp[i]->SetMaterial(0, DynamicMaterial[i]);

			FTransform WorldTransform =  MeshComp[i]->GetComponentToWorld();
			OriginLocation[i] = WorldTransform.GetLocation();
			OriginRotation[i] = WorldTransform.GetRotation();
		}
	}
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACBoxBase_MultiCast::StaticClass(), actors);
	if (actors.Num() < 1)
	{
		return;
	}

	ACBoxBase_MultiCast* Tirgger = Cast<ACBoxBase_MultiCast>(actors[0]);
	Tirgger->OnMulticastBeginOverlap.AddUObject(this, &ACUbes::Drop);
}

void ACUbes::Drop(int32 InIndex, FLinearColor InColor)
{
	for (int32 i = 0; i < 3; i++)
	{
		DynamicMaterial[i]->SetVectorParameterValue("BaseColor", FLinearColor::White);
		MeshComp[i]->SetSimulatePhysics(false);
		MeshComp[i]->SetWorldLocation(OriginLocation[i]);
		MeshComp[i]->SetWorldRotation(OriginRotation[i]);
	}


	MeshComp[InIndex]->SetSimulatePhysics(true);
	DynamicMaterial[InIndex]->SetVectorParameterValue("BaseColor", InColor);
}


