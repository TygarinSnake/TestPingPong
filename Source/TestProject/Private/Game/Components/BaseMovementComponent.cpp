#include "Game/Components/BaseMovementComponent.h"

UBaseMovementComponent::UBaseMovementComponent()
{
    MoveSpeed = 600.0f;
}

void UBaseMovementComponent::BeginPlay()
{
    Super::BeginPlay();
    Owner = GetOwner();
}

void UBaseMovementComponent::AddInputVector(const FVector& Direction)
{
    check(Owner);
    FVector Movement = Direction.GetSafeNormal() * MoveSpeed * GetWorld()->GetDeltaSeconds();

    Owner->AddActorWorldOffset(Movement, true);
}

void UBaseMovementComponent::SetMoveSpeed(float NewSpeed)
{
    if (NewSpeed >= 0)
    {
        MoveSpeed = NewSpeed;
    }
}
