#include "Game/GameModes/PPGameMode.h"

#include "EngineUtils.h"
#include "Engine/World.h"
#include "GameFramework/SpectatorPawn.h"

#include "Game/GameStates/PPGameState.h"
#include "Game/Actors/GateActor.h"
#include "Game/Actors/BallActor.h"

DEFINE_LOG_CATEGORY_STATIC(LogPPGameMode, All, All);

APPGameMode::APPGameMode()
{
    SpectatorClass = ASpectatorPawn::StaticClass();
    GameStateClass = APPGameState::StaticClass();

    StartPositionBall = FVector(0.f, 0.f, 150.f);

    bReplicates = true;

    NumPlayerForStartGame = 2;
    ConnectedPlayers = 0;
}

void APPGameMode::BeginPlay()
{
    Super::BeginPlay();
    SubscribeOnGoalEvent();

    BallActor = GetWorld()->SpawnActor<ABallActor>(BallActorClass, StartPositionBall, FRotator::ZeroRotator);
    check(BallActor);
    BallActor->SetIsMove(false);
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
    APPGameState* PPGameState = GetGameState<APPGameState>();

    if (PPGameState)
    {
        PPGameState->Multicast_UpdateScoreboard(GateName);
    }

    check(BallActor);
    bool bTeleported = BallActor->TeleportTo(StartPositionBall, BallActor->GetActorRotation());

    BallActor->SetDirectionMovement(GetRandomDirection());

    if (bTeleported)
    {
        UE_LOG(LogTemp, Display, TEXT("Teleportation ball successful!"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Teleportation ball failed!"));
    }
}

FORCEINLINE FVector APPGameMode::GetRandomDirection() const
{
    return FVector(
        FMath::RandBool() ? 1.f : -1.f,
        FMath::RandBool() ? 1.f : -1.f,
        0.f);
}

void APPGameMode::PostLogin(APlayerController* NewPlayer)
{
    Super::PostLogin(NewPlayer);

    check(NewPlayer);
    UE_LOG(LogTemp, Log, TEXT("Player %s has joined as a spectator"), *NewPlayer->GetName());
}

void APPGameMode::OnPostLogin(APlayerController* NewPlayer)
{
    check(NewPlayer);
    UE_LOG(LogPPGameMode, Display, TEXT("Player %s has joined the game"), *NewPlayer->GetName());
    ++ConnectedPlayers;

    CheckConnectedPlayerForStartGame();
}

FORCEINLINE void APPGameMode::CheckConnectedPlayerForStartGame()
{
    if (ConnectedPlayers >= NumPlayerForStartGame)
    {
        StartGame();
    }
    else
    {
        WaitStartGame();
    }
}

void APPGameMode::StartGame()
{
    if (APPGameState* PPGameState = GetGameState<APPGameState>())
    {
        PPGameState->Multicast_NotifyPlayerStartGame();
    }

    FVector StartBallDirection = GetRandomDirection();

    check(BallActor);
    BallActor->SetDirectionMovement(StartBallDirection);
    BallActor->SetIsMove(true);

    UE_LOG(LogPPGameMode, Display, TEXT("The game has started!"));
}

void APPGameMode::WaitStartGame()
{
    if (APPGameState* PPGameState = GetGameState<APPGameState>())
    {
        PPGameState->Multicast_NotifyPlayerStopGame();
    }

    check(BallActor);
    bool bTeleported = BallActor->TeleportTo(StartPositionBall, BallActor->GetActorRotation());
    BallActor->SetIsMove(false);

    UE_LOG(LogPPGameMode, Display, TEXT("The game has stoped!"));
}

void APPGameMode::Logout(AController* DisconnectPlayer)
{
    Super::Logout(DisconnectPlayer);

    check(DisconnectPlayer);
    UE_LOG(LogPPGameMode, Display, TEXT("Player %s has joined the game"), *DisconnectPlayer->GetName());
    --ConnectedPlayers;
    CheckConnectedPlayerForStartGame();
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
