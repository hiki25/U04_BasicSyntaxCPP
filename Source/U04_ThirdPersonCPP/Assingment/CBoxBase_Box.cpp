#include "CBoxBase_Box.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"



ACBoxBase_Box::ACBoxBase_Box()
{
	ChestBottom = CreateDefaultSubobject<UStaticMeshComponent>("ChestBottm");
	 ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset_Bottom (TEXT("StaticMesh'/Game/Assingment/Chest/SM_ChestBottom.SM_ChestBottom'"));
	 if (MeshAsset_Bottom.Succeeded())
	 {
		 ChestBottom -> SetStaticMesh(MeshAsset_Bottom.Object);
	 }

	 ChestTop = CreateDefaultSubobject<UStaticMeshComponent>("ChestTop");
	 ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset_Top (TEXT("StaticMesh'/Game/Assingment/Chest/SM_ChestTop.SM_ChestTop'"));
	 if (MeshAsset_Top.Succeeded())
	 {
		 ChestTop -> SetStaticMesh(MeshAsset_Top.Object);
	 }

	 ChestBottom->SetupAttachment(RootComp);
	 ChestTop->SetupAttachment(RootComp);


	 ChestBottom->SetRelativeRotation(FRotator(0, -180, 0));
	 ChestBottom->SetRelativeLocation(FVector(50, 0, 0));
	 
	 ChestTop->SetRelativeRotation(FRotator(0, -180, 0));
	 ChestTop->SetRelativeLocation(FVector(50, 0, 0));
}

void ACBoxBase_Box::OnConstruction(const FTransform& Transform)
{
	OnActorBeginOverlap.AddDynamic(this, &ACBoxBase_Box::ActorBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &ACBoxBase_Box::ActorEndOverlap);

	UObject* ConstantAsset = StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("/Game/Assingment/Chest/MI_Chest"));
	UMaterialInstanceConstant* MaterialAsset = Cast<UMaterialInstanceConstant>(ConstantAsset);

	ChestMaterialDynamic = UMaterialInstanceDynamic::Create(MaterialAsset, nullptr);
	ChestMaterialDynamic->SetVectorParameterValue("Emissive",ChestColor);

	ChestBottom->SetMaterial(0, ChestMaterialDynamic);
	ChestTop->SetMaterial(0, ChestMaterialDynamic);
}

void ACBoxBase_Box::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Player = Cast<ACPlayer>(OtherActor);
	
	
}

void ACBoxBase_Box::ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Player = nullptr;
}



void ACBoxBase_Box::OpenTheDoor(float InRotator)
{
	ChestTop->SetRelativeRotation(FRotator(InRotator, -180, 0));
}


