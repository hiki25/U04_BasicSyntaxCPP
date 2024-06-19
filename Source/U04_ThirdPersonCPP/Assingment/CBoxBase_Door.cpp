#include "CBoxBase_Door.h"
#include "Global.h"
#include "CPlayer.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"


ACBoxBase_Door::ACBoxBase_Door()
{
	
	Door = CreateDefaultSubobject<UStaticMeshComponent>("Door");
	 ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset_Door (TEXT("StaticMesh'/Game/Assingment/Door/Props/SM_Door.SM_Door'"));
	 if (MeshAsset_Door.Succeeded())
	 {
		 Door-> SetStaticMesh(MeshAsset_Door.Object);
	 }

	 DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>("DoorFrame");
	 ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset_Frame(TEXT("StaticMesh'/Game/Assingment/Door/Props/SM_DoorFrame.SM_DoorFrame'"));
	 if (MeshAsset_Frame.Succeeded())
	 {
		 DoorFrame-> SetStaticMesh(MeshAsset_Frame.Object);
	 }

	 Door->SetupAttachment(RootComp);
	 DoorFrame->SetupAttachment(RootComp);

	 Door->SetRelativeLocation(FVector(0, 47, -88));
	 DoorFrame->SetRelativeLocation(FVector(0, 0, -88));
	 
	 
}

void ACBoxBase_Door::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &ACBoxBase_Door::ActorBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &ACBoxBase_Door::ActorBeginOverlap);
}

void ACBoxBase_Door::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Player = Cast<ACPlayer>(OtherActor);
}

void ACBoxBase_Door::ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Player = nullptr;
}

void ACBoxBase_Door::OnConstruction(const FTransform& Transform)
{
	UObject* DoorAsset = StaticLoadObject(UMaterialInstanceConstant::StaticClass(), this, TEXT("/Game/Assingment/Door/Materials/MI_Door"));
	UMaterialInstanceConstant* MaterialAsset = Cast<UMaterialInstanceConstant>(DoorAsset);
	UObject* DoorFrameAsset = StaticLoadObject(UMaterialInstanceConstant::StaticClass(), this, TEXT("/Game/Assingment/Door/Materials/MI_Frame"));
	UMaterialInstanceConstant* MaterialFrameAsset = Cast<UMaterialInstanceConstant>(DoorFrameAsset);


	if (MaterialAsset)
	{
		DynamicMaterial = UMaterialInstanceDynamic::Create(MaterialAsset, nullptr);
		Door->SetMaterial(0, DynamicMaterial);
		DynamicMaterial->SetVectorParameterValue("ColorDoor", MaterialColor);
	}

	if (DoorFrameAsset)
	{
		DynamicMaterial = UMaterialInstanceDynamic::Create(MaterialFrameAsset, nullptr);
		DoorFrame->SetMaterial(0, DynamicMaterial);
		DynamicMaterial->SetVectorParameterValue("Color", MaterialColor);
	}
	
}



void ACBoxBase_Door::OpenTheDoor(float InRotator)
{

}


