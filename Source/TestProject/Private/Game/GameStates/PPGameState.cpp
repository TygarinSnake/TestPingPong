#include "Game/GameStates/PPGameState.h"

#include "Net/UnrealNetwork.h"

#include "Game/HUDs/PPHUD.h"

inline void PlayerControllerHUDIIteration(void (*Func)(APPHUD*, TMap<FString, int32>*), UWorld* World, TMap<FString, int32>* Map = nullptr)
{
    for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
    {
        APlayerController* PlayerController = It->Get();
        if (APPHUD* HUD = Cast<APPHUD>(PlayerController->GetHUD()))
        {
            Func(HUD, Map);
        }
    }
}

APPGameState::APPGameState()
{
    Scores.Add("Top", 0);
    Scores.Add("Bottom", 0);

    bReplicates = true;
}

void APPGameState::BeginPlay()
{
    Super::BeginPlay();
    UpdatePlayerScoreboardWidget();
}

FORCEINLINE void APPGameState::UpdatePlayerScoreboardWidget()
{
    PlayerControllerHUDIIteration(
        [](APPHUD* HUD, TMap<FString, int32>* Map)
        {
            HUD->SetScoreboardData(*Map);
        },
        GetWorld(), &Scores);
}

void APPGameState::Multicast_NotifyPlayerStartGame_Implementation()
{
    PlayerControllerHUDIIteration(
        [](APPHUD* HUD, TMap<FString, int32>* Map)
        {
            HUD->HideWaitConnectionWidget();
            HUD->ShowScoreboardWidget();
            HUD->SetScoreboardData(*Map);
        },
        GetWorld(), &Scores);
}

void APPGameState::Multicast_NotifyPlayerStopGame_Implementation()
{
    PlayerControllerHUDIIteration(
        [](APPHUD* HUD, TMap<FString, int32>* Map)
        {
            HUD->ShowWaitConnectionWidget();
            HUD->HideScoreboardWidget();
        },
        GetWorld());
}

void APPGameState::Multicast_UpdateScoreboard_Implementation(const FString& GateName)
{
    int32* ExistGate = Scores.Find(GateName);
    ExistGate ? ++*ExistGate : Scores.Add(GateName, 1);

    UpdatePlayerScoreboardWidget();
}
