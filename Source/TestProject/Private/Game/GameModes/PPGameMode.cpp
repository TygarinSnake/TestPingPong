#include "Game/GameModes/PPGameMode.h"

#include "EngineUtils.h"
#include "Engine/World.h"

#include "Game/HUDs/PPHUD.h"
#include "Game/GameStates/PPGameState.h"
#include "Game/Actors/GateActor.h"

DEFINE_LOG_CATEGORY_STATIC(LogPPGameMode, All, All);

APPGameMode::APPGameMode()
{
    HUDClass = APPHUD::StaticClass();
    GameStateClass = APPGameState::StaticClass();

    StartPositionBall = FVector(0.f, 0.f, 150.f);

    bReplicates = true;
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
    APPGameState* PPameState = GetGameState<APPGameState>();

    if (PPameState)
    {
        PPameState->Multicast_UpdateScoreboard(GateName);
    }  

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
