#include "Game/Pawns/PlayerBoardPawn.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "Game/Components/BaseMovementComponent.h"

APlayerBoardPawn::APlayerBoardPawn()
{
    PawnMovement = CreateDefaultSubobject<UBaseMovementComponent>(TEXT("MovementComponent"));
    check(PawnMovement);
}

void APlayerBoardPawn::BeginPlay()
{
    Super::BeginPlay();

    check(PawnMovement);
    PawnMovement->SetMoveSpeed(MoveSpeed);
}

FORCEINLINE void APlayerBoardPawn::AddMovement_Implementation(FVector2D Scale)
{
    check(PawnMovement);
    FVector direction = GetActorRightVector();
    PawnMovement->AddInputVector(direction * Scale.X);
}