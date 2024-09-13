#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Movable.generated.h"

UINTERFACE(MinimalAPI)
class UMovable : public UInterface
{
    GENERATED_BODY()
};

class TESTPROJECT_API IMovable
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Movement")
    void AddMovement(FVector2D Scale);
};
