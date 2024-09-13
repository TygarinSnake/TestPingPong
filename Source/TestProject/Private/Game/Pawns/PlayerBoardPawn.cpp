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

    PawnMovement->SetMoveSpeed(MoveSpeed);
}

FORCEINLINE void APlayerBoardPawn::MoveRight(const FInputActionValue& InputValue)
{
    float ScaleValue = InputValue.Get<float>();
    AddMovement_Implementation(ScaleValue);
}

FORCEINLINE void APlayerBoardPawn::AddMovement_Implementation(float Scale)
{
    check(PawnMovement);
    FVector direction = GetActorRightVector();
    PawnMovement->AddInputVector(direction * Scale);
}