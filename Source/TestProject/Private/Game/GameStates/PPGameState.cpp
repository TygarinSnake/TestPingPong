#include "Game/GameStates/PPGameState.h"

#include "Net/UnrealNetwork.h"

#include "Game/HUDs/PPHUD.h"

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

void APPGameState::UpdatePlayerScoreboardWidget()
{
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        APlayerController* PlayerController = It->Get();
        if (APPHUD* HUD = Cast<APPHUD>(PlayerController->GetHUD()))
        {
            HUD->SetScoreboardData(Scores);
        }
    }
}

void APPGameState::Multicast_UpdateScoreboard_Implementation(const FString& GateName)
{
    int32* ExistGate = Scores.Find(GateName);
    ExistGate ? ++*ExistGate : Scores.Add(GateName, 1);

    UpdatePlayerScoreboardWidget();
}
