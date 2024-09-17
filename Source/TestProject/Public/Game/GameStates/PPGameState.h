#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PPGameState.generated.h"

class APlayerController;

UCLASS()
class TESTPROJECT_API APPGameState : public AGameStateBase
{
    GENERATED_BODY()

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Scores", meta = (AllowPrivateAccess = "true"))
    TMap<FString, int32> Scores;

protected:
    virtual void BeginPlay() override;

    void UpdatePlayerScoreboardWidget();

public:
    APPGameState();

    UFUNCTION(NetMulticast, Reliable)
    void Multicast_UpdateScoreboard(const FString& GateName);

    UFUNCTION(NetMulticast, Reliable)
    void Multicast_NotifyPlayerStartGame();

    UFUNCTION(NetMulticast, Reliable)
    void Multicast_NotifyPlayerStopGame();
};
