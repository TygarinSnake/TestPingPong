#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseMovementComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TESTPROJECT_API UBaseMovementComponent : public UActorComponent
{
    GENERATED_BODY()

private:
    UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0"), Category = "Movement")
    float Velocity;

    TObjectPtr<AActor> Owner;

protected:
    virtual void BeginPlay() override;

public:
    UBaseMovementComponent();

    void AddInputVector(const FVector& Direction);
    void SetVelocity(float NewSpeed);
};
