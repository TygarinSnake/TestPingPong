#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BallActor.generated.h"

class UBaseMovementComponent;
class USphereComponent;

UCLASS(Abstract)
class TESTPROJECT_API ABallActor : public AActor
{
    GENERATED_BODY()

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UBaseMovementComponent> MovementComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<USphereComponent> CollisionComponent;

    UPROPERTY(EditAnywhere, meta = (ClampMin = "0.0"), Category = "Move")
    float MoveSpeed;

    FVector Direction;

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

    FVector ReflectionVector(const FVector& CurrentDirection, const FHitResult& Hit);

public:
    ABallActor();

    virtual void Tick(float DeltaTime) override;

    FVector GetDirectionMovement() const;
    void SetDirectionMovement(FVector VectorDirection);
};
