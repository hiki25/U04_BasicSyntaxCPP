#include "CAnimInstance.h"
#include "GameFramework/Character.h"
#include "Utilities/CHelpers.h"

void UCAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

}

void UCAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	ACharacter* Character = Cast<ACharacter>(TryGetPawnOwner());

	CheckNull(Character);
	Speed = Character->GetVelocity().Size2D();
	Direction = CalculateDirection(Character->GetVelocity(), Character->GetControlRotation());
}