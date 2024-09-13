#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

#include "Game/Interfaces/Movable.h"

#include "PlayerBoardPawn.generated.h"

class UInputMappingContext;
class UInputAction;
class UBaseMovementComponent;
struct FInputActionValue;

UCLASS()
class TESTPROJECT_API APlayerBoardPawn : public APawn, public IMovable
{
    GENERATED_BODY()

private:
    UPROPERTY(EditAnywhere, Category = "Input")
    TObjectPtr<UInputMappingContext> PlayerMappingContext;

    UPROPERTY(EditAnywhere, Category = "Input")
    TObjectPtr<UInputAction> IA_Move;

    UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0"), Category = "Move")
    float MoveSpeed;

    UPROPERTY(Category = Pawn, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UBaseMovementComponent> PawnMovement;

protected:
    virtual void BeginPlay() override;

public:
    APlayerBoardPawn();

    void MoveRight(const FInputActionValue& InputValue);

    // Implementation IMovable
    virtual void AddMovement_Implementation(float Scale) override;
};