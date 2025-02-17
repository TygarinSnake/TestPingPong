#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Game/Interfaces/Movable.h"

#include "PlayerBoardPawn.generated.h"

class UBaseMovementComponent;
struct FInputActionValue;

UCLASS(Abstract)
class TESTPROJECT_API APlayerBoardPawn : public APawn, public IMovable
{
    GENERATED_BODY()

private:
    UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0"), Category = "Move")
    float MoveMaxSpeed;

    UPROPERTY(Category = Pawn, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UBaseMovementComponent> MovementComponent;

protected:
    virtual void BeginPlay() override;

public:
    APlayerBoardPawn();

    // Implementation IMovable
    virtual void AddMovement_Implementation(FVector2D Scale) override;
};