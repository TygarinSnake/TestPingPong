#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BaseMovementComponent.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TESTPROJECT_API UBaseMovementComponent : public UActorComponent
{
    GENERATED_BODY()

private:
    UPROPERTY(Replicated = COND_InitialOnly, EditAnywhere, meta = (ClampMin = "0.0"), Category = "Movement")
    float MaxSpeed;

    UPROPERTY(Replicated = COND_InitialOnly, EditAnywhere, Category = "Movement")
    float InterpSpeed;

    UPROPERTY(ReplicatedUsing = OnRep_InputVector)
    FVector InputVector;

    UPROPERTY(Replicated = COND_InitialOnly, EditAnywhere, Category = "Collision")
    bool bIsCollisoin;

     bool bIsHavePlayerControlled;

    FVector TargetPosition;

    TObjectPtr<AActor> Owner;

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnRep_InputVector();

public:
    UBaseMovementComponent();

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void AddInputVector(const FVector& Direction);

    UFUNCTION(BlueprintCallable, Category = "Movement")
    void SetMaxSpeed(float NewVelocity);
    void SetIsPossesed(bool IsPossesed);

    UFUNCTION(Server, Unreliable)
    void Server_AddInputVector(const FVector& Direction);

    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
