#include "Game/GameModes/PPGameMode.h"

#include "EngineUtils.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

#include "Game/HUDs/PPHUD.h"
#include "Game/Actors/GateActor.h"

DEFINE_LOG_CATEGORY_STATIC(LogPPGameMode, All, All);

APPGameMode::APPGameMode()
{
    HUDClass = APPHUD::StaticClass();

    Scores.Add("Top", 0);
    Scores.Add("Bottom", 0);
    StartPositionBall = FVector(0.f, 0.f, 150.f);
}

void APPGameMode::BeginPlay()
{
    Super::BeginPlay();
    SubscribeOnGoalEvent();
}

void APPGameMode::SubscribeOnGoalEvent()
{
    if (UWorld* World = GetWorld())
    {
        for (TActorIterator<AGateActor> It(World); It; ++It)
        {
            AGateActor* GateActor = *It;
            if (GateActor)
            {
                GateActor->OnGoalEvent.AddDynamic(this, &ThisClass::OnGoalEventHandler);
                UE_LOG(LogPPGameMode, Display, TEXT("%s subscribe on OnGoalEvent: %s"), *GetName(), *GateActor->GetName());
            }
        }
    }
}

void APPGameMode::OnGoalEventHandler(FString GateName, AActor* OtherActor)
{
    int32* ExistGate = Scores.Find(GateName);
    ExistGate ? ++*ExistGate : Scores.Add(GateName, 1);
    UpdateScoreboard(Scores);

    check(OtherActor);
    bool bTeleported = OtherActor->TeleportTo(StartPositionBall, OtherActor->GetActorRotation());

    if (bTeleported)
    {
        UE_LOG(LogTemp, Display, TEXT("Teleportation actor successful!"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Teleportation actor failed!"));
    }
}

void APPGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
    UnsubscribeOnGoalEvent();
}

void APPGameMode::UnsubscribeOnGoalEvent()
{
    if (UWorld* World = GetWorld())
    {
        for (TActorIterator<AGateActor> It(World); It; ++It)
        {
            AGateActor* GateActor = *It;
            if (GateActor)
            {
                GateActor->OnGoalEvent.RemoveDynamic(this, &ThisClass::OnGoalEventHandler);
                UE_LOG(LogPPGameMode, Display, TEXT("%s unsubscribe on OnGoalEvent: %s"), *GetName(), *GateActor->GetName());
            }
        }
    }
}

void APPGameMode::UpdateScoreboard(const TMap<FString, int32>& NewScore)
{
    for (TActorIterator<APlayerController> It(GetWorld()); It; ++It)
    {
        APlayerController* PlayerController = *It;
        if (APPHUD* HUD = Cast<APPHUD>(PlayerController->GetHUD()))
        {
            HUD->SetScoreboardData(NewScore);
        }
    }
}
