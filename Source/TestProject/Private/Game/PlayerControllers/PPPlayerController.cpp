#include "Game/PlayerControllers/PPPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "Game/GameModes/PPGameMode.h"
#include "Game/Interfaces/Movable.h"

void APPPlayerController::BeginPlay()
{
    Super::BeginPlay();
    SetupMappingContext();
    Client_NotifyLoaded();
}

FORCEINLINE void APPPlayerController::SetupMappingContext()
{
    if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
                ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
        {
            Subsystem->AddMappingContext(PlayerMappingContext, 0);
            SetupInputActions();
        }
    }
}

FORCEINLINE void APPPlayerController::SetupInputActions()
{
    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
    {
        EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ThisClass::MoveRight);
    }
}

void APPPlayerController::Client_NotifyLoaded_Implementation()
{
    Server_PlayerLoaded();
}

void APPPlayerController::Server_PlayerLoaded_Implementation()
{
    if (APPGameMode* MyGameMode = GetWorld()->GetAuthGameMode<APPGameMode>())
    {
        MyGameMode->OnPostLogin(this);
    }
}

APPPlayerController::APPPlayerController()
{
    bReplicates = true;
}

void APPPlayerController::MoveRight(const FInputActionValue& InputValue)
{
    if (GetPawn())
    {
        const float ScaleValue = InputValue.Get<float>();
        FVector2D ScaleVector = FVector2D(ScaleValue, 0.f);
        IMovable::Execute_AddMovement(GetPawn(), ScaleVector);
    }
}
