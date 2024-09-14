#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PPHUD.generated.h"

class UScoreboardUserWidget;

UCLASS()
class TESTPROJECT_API APPHUD : public AHUD
{
    GENERATED_BODY()

private:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<UScoreboardUserWidget> ScoreboardWidgetClass;

    TObjectPtr<UScoreboardUserWidget> ScoreboardWidget;

protected:
    virtual void BeginPlay() override;
    void EndPlay(const EEndPlayReason::Type EndPlayReason);

public:
    void RefreshScoreboard(const TMap<FString, int32>& NewScoreMap);
};
