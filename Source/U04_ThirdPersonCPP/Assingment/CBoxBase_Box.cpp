#include "CBoxBase_Box.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "CPlayer.h"


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

void ACBoxBase_Box::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	Super::ActorBeginOverlap(OverlappedActor, OtherActor);
	ACPlayer* Player = Cast<ACPlayer>(OtherActor);
	
	if(Player->bOpen)
	{
		CLog::Print("Open");
		OpenTheDoor(50.f);
	}
	else
	{
		CLog::Print("false");
	}
	
}

void ACBoxBase_Box::OpenTheDoor(float InRotator)
{
	ChestTop->SetRelativeRotation(FRotator(InRotator, -180, 0));
}


