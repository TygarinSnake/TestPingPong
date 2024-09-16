#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GateActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnGoalEvent, FString, GateName, AActor*, OtherActor);

class UBoxComponent;

UCLASS()
class TESTPROJECT_API AGateActor : public AActor
{
    GENERATED_BODY()

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<UBoxComponent> CollisionComponent;

    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Name", meta = (AllowPrivateAccess = "true"))
    FString GateNameWinnerSide;

public:
    UPROPERTY(BlueprintAssignable, Category = "Events")
    FOnGoalEvent OnGoalEvent;

protected:
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
    AGateActor();

    UFUNCTION(Server, Reliable)
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
        bool bFromSweep, const FHitResult& SweepResult);
};
