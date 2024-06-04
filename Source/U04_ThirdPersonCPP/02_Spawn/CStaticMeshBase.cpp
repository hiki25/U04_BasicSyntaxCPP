#include "CStaticMeshBase.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"

// Sets default values
ACStaticMeshBase::ACStaticMeshBase()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	//RootComponent = MeshComp;
	SetRootComponent(MeshComp);

	ConstructorHelpers::FObjectFinder<UStaticMesh>meshAsset(TEXT("/Game/StaticMeshes/SM_Cube"));

	if(meshAsset.Succeeded())
		MeshComp->SetStaticMesh(meshAsset.Object);
}

void ACStaticMeshBase::BeginPlay()
{
	Super::BeginPlay();

	UMaterialInstanceConstant* materialAsset = 
	Cast<UMaterialInstanceConstant>(StaticLoadObject(UMaterialInstanceConstant :: StaticClass(), nullptr, TEXT("/Game/Materials/MI_StaticMesh_Inst")));

	if (materialAsset)
	{
		DynamicMaterial = UMaterialInstanceDynamic::Create(materialAsset, this);
		MeshComp->SetMaterial(0,DynamicMaterial);
	}

	UKismetArrayLibrary::K2_SetTimer(this, "UpdateParameters", 1.f, true);
}

void ACStaticMeshBase::UpdateParameters()
{

	DynamicMaterial -> SetVectorParameterValue("BaseColor",)
}



