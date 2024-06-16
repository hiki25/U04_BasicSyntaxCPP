#include "CBoxBase_Door.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"

ACBoxBase_Door::ACBoxBase_Door()
{
	Door = CreateDefaultSubobject<UStaticMeshComponent>("DoorComp");
	ConstructorHelpers::FObjectFinder<UStaticMesh> DoorAsset(TEXT("/Game/Assingment/Door/Props/SM_Door"));
	if (DoorAsset.Succeeded())
	{
		Door->SetStaticMesh(DoorAsset.Object);
	}

	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>("FrameComp");
	ConstructorHelpers::FObjectFinder<UStaticMesh> DoorFrameAsset(TEXT("/Game/Assingment/Door/Props/SM_DoorFrame"));
	if (DoorFrameAsset.Succeeded())
	{
		DoorFrame->SetStaticMesh(DoorFrameAsset.Object);
	}

	Door->SetupAttachment(DoorFrame);
	Door->SetRelativeLocation(FVector(0, 45, 0));
	DoorFrame->SetupAttachment(RootComp);

	TextRenderComp->SetRelativeLocation(FVector(0, 0, 250));
	

}

void ACBoxBase_Door::BeginPlay()
{
	Super::BeginPlay();
}

void ACBoxBase_Door::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	OnActorBeginOverlap.AddDynamic(this, &ACBoxBase_Door::ActorBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &ACBoxBase_Door::ActorEndOverlap);

	UObject* DoorObjectAsset = StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("/Game/Assingment/Door/Materials/MI_Door"));
	UMaterialInstanceConstant* MaterialAsset = Cast<UMaterialInstanceConstant>(DoorObjectAsset);
	DoorDynamicMaterial = UMaterialInstanceDynamic::Create(MaterialAsset, nullptr);
	Door->SetMaterial(0, DoorDynamicMaterial);
	DoorDynamicMaterial->SetVectorParameterValue("ColorDoor", DoorColor);

	UObject* FrameObjectAsset = StaticLoadObject(UMaterialInstanceConstant::StaticClass(), nullptr, TEXT("/Game/Assingment/Door/Materials/MI_Frame"));
	UMaterialInstanceConstant* MaterialFrameAsset = Cast<UMaterialInstanceConstant>(FrameObjectAsset);
	FrameDynamicMaterial = UMaterialInstanceDynamic::Create(MaterialFrameAsset, nullptr);
	DoorFrame->SetMaterial(0, FrameDynamicMaterial);
	FrameDynamicMaterial->SetVectorParameterValue("Color", DoorColor);

	TextRenderComp->SetText(TEXT("Please " + Key.ToString() + " Key"));
	
}

void ACBoxBase_Door::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Super::ActorBeginOverlap(OverlappedActor, OtherActor);
}

void ACBoxBase_Door::ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Super::ActorEndOverlap(OverlappedActor, OtherActor);
}

void ACBoxBase_Door::OpenTheDoor(float InRotator)
{
	if (bOpen == false)
	{
		Door->SetRelativeRotation(FRotator(0, InRotator, 0));
		bOpen = true;
	}
}