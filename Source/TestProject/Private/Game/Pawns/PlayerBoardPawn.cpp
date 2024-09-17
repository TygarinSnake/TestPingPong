#include "Game/Pawns/PlayerBoardPawn.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "Game/Components/BaseMovementComponent.h"

APlayerBoardPawn::APlayerBoardPawn()
{
    MoveMaxSpeed = 600.f;
    MovementComponent = CreateDefaultSubobject<UBaseMovementComponent>(TEXT("MovementComponent"));
    check(MovementComponent);
}

void APlayerBoardPawn::BeginPlay()
{
    Super::BeginPlay();

    check(MovementComponent);
    MovementComponent->SetMaxSpeed(MoveMaxSpeed);
}

void APlayerBoardPawn::AddMovement_Implementation(FVector2D Scale)
{
    check(MovementComponent);
    FVector Direction = GetActorRightVector();
    MovementComponent->AddInputVector(Direction * Scale.X);
}