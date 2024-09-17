#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PPGameMode.generated.h"

class ABallActor;

UCLASS(Abstract)
class TESTPROJECT_API APPGameMode : public AGameModeBase
{
    GENERATED_BODY()

private:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Target", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<ABallActor> BallActorClass;

    TObjectPtr<ABallActor> BallActor;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target", meta = (AllowPrivateAccess = "true"))
    FVector StartPositionBall;

    UPROPERTY(EditDefaultsOnly, Category = "Start game")
    int32 NumPlayerForStartGame;
    int32 ConnectedPlayers;

protected:
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    virtual void PostLogin(APlayerController* NewPlayer) override;

    void SubscribeOnGoalEvent();
    void UnsubscribeOnGoalEvent();

    void CheckConnectedPlayerForStartGame();
    FVector GetRandomDirection() const;

public:
    APPGameMode();

    void OnPostLogin(APlayerController* NewPlayer);
    virtual void Logout(AController* DisconnectPlayer) override;

    UFUNCTION()
    void OnGoalEventHandler(FString GateName, AActor* OtherActor);

    void StartGame();
    void WaitStartGame();
};
