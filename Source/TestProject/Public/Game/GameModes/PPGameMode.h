#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PPGameMode.generated.h"

UCLASS()
class TESTPROJECT_API APPGameMode : public AGameModeBase
{
    GENERATED_BODY()

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Scores", meta = (AllowPrivateAccess = "true"))
    TMap<FString, int32> Scores;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target", meta = (AllowPrivateAccess = "true"))
    TObjectPtr<AActor> StartPositionBall;

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
    APPGameMode();

    UFUNCTION()
    void OnGoalEventHandler(FString GateName, AActor* OtherActor);
    void UpdateScoreboard(const TMap<FString, int32>& NewScore);
    void SubscribeOnGoalEvent();
    void UnsubscribeOnGoalEvent();
};
