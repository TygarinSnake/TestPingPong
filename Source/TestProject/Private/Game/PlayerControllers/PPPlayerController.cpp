#include "Game/PlayerControllers/PPPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

#include "Game/Interfaces/Movable.h"

void APPPlayerController::BeginPlay()
{
    Super::BeginPlay();

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

void APPPlayerController::SetupInputActions()
{
    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
    {
        EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &ThisClass::Move);
    }
}

FORCEINLINE void APPPlayerController::Move(const FInputActionValue& InputValue)
{
    check(GetPawn());
    const float ScaleValue = InputValue.Get<float>();
    FVector2D ScaleVector = FVector2D(ScaleValue, 0.f);
    IMovable::Execute_AddMovement(GetPawn(), ScaleVector);
}
