#include "U04_ThirdPersonCPPGameModeBase.h"
#include "CPlayer.h"

AU04_ThirdPersonCPPGameModeBase::AU04_ThirdPersonCPPGameModeBase()
{
	ConstructorHelpers::FClassFinder<APawn>pawnAsset(TEXT("Blueprint'/Game/BPCPlayer.BPCPlayer_C'"));

	if(pawnAsset.Succeeded())
	DefaultPawnClass = pawnAsset.Class;
}
