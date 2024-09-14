#include "Game/Components/BaseMovementComponent.h"

UBaseMovementComponent::UBaseMovementComponent()
{
    Velocity = 600.0f;
}

void UBaseMovementComponent::BeginPlay()
{
    Super::BeginPlay();
    Owner = GetOwner();
}

FORCEINLINE void UBaseMovementComponent::AddInputVector(const FVector& Direction)
{
    check(Owner);
    FVector Movement = Direction.GetSafeNormal() * Velocity * GetWorld()->GetDeltaSeconds();

    Owner->AddActorWorldOffset(Movement, true);
}

void UBaseMovementComponent::SetVelocity(float NewSpeed)
{
    if (NewSpeed >= 0)
    {
        Velocity = NewSpeed;
    }
}
