#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PPPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class TESTPROJECT_API APPPlayerController : public APlayerController
{
    GENERATED_BODY()

private:
    UPROPERTY(EditAnywhere, Category = "Input")
    TObjectPtr<UInputMappingContext> PlayerMappingContext;

    UPROPERTY(EditAnywhere, Category = "Input")
    TObjectPtr<UInputAction> IA_Move;

protected:
    virtual void BeginPlay() override;
    void SetupMappingContext();
    void SetupInputActions();

public:
    void Move(const FInputActionValue& InputValue);
};
