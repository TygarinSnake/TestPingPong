#include "Game/Components/BaseMovementComponent.h"

#include "Net/UnrealNetwork.h"

UBaseMovementComponent::UBaseMovementComponent()
{
    MaxSpeed = 600.0f;
    InterpSpeed = 5.f;
    bIsCollisoin = true;
    TargetPosition = FVector::Zero();
    SetIsReplicatedByDefault(true);
}

void UBaseMovementComponent::BeginPlay()
{
    Super::BeginPlay();
    Owner = GetOwner();
}

FORCEINLINE void UBaseMovementComponent::AddInputVector(const FVector& Direction)
{
    if (GetOwnerRole() != ROLE_Authority)
    {
        Server_AddInputVector(Direction);
    }

    check(Owner);
    InputVector = Direction.GetSafeNormal() * MaxSpeed * GetWorld()->GetDeltaSeconds();
    TargetPosition = Owner->GetActorLocation() + InputVector;

    Owner->SetActorLocation(TargetPosition, bIsCollisoin);
}

void UBaseMovementComponent::Server_AddInputVector_Implementation(const FVector& Direction)
{
    AddInputVector(Direction);
}

void UBaseMovementComponent::OnRep_InputVector()
{
    if (Owner)
    {
        TargetPosition = Owner->GetActorLocation() + InputVector;
        Owner->SetActorLocation(TargetPosition, bIsCollisoin);
    }
}

void UBaseMovementComponent::SetMaxSpeed(float NewSpeed)
{
    if (GetOwnerRole() != ROLE_Authority)
    {
        return;
    }

    if (NewSpeed >= 0)
    {
        MaxSpeed = NewSpeed;
    }
}

void UBaseMovementComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(UBaseMovementComponent, MaxSpeed);
    DOREPLIFETIME(UBaseMovementComponent, InputVector);
    DOREPLIFETIME(UBaseMovementComponent, bIsCollisoin);
    DOREPLIFETIME(UBaseMovementComponent, InterpSpeed);
}
