#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BallActor.generated.h"

class UFloatingPawnMovement;

UCLASS()
class TESTPROJECT_API ABallActor : public AActor
{
    GENERATED_BODY()

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UFloatingPawnMovement> FloatingPawnMovement;

public:
    // Sets default values for this actor's properties
    ABallActor();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
};
