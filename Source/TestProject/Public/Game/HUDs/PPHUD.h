#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PPHUD.generated.h"

class UUserWidget;
class UScoreboardUserWidget;

UCLASS(Abstract)
class TESTPROJECT_API APPHUD : public AHUD
{
    GENERATED_BODY()

private:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<UScoreboardUserWidget> ScoreboardWidgetClass;
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<UUserWidget> WaitConnectionWidgetClass;

    TObjectPtr<UScoreboardUserWidget> ScoreboardWidget;
    TObjectPtr<UUserWidget> WaitConnectionWidget;

protected:
    virtual void BeginPlay() override;
    void EndPlay(const EEndPlayReason::Type EndPlayReason);

public:
     void SetScoreboardData(TMap<FString, int32> NewScoreMap);
     void ShowScoreboardWidget();
     void ShowWaitConnectionWidget();
     void HideScoreboardWidget();
     void HideWaitConnectionWidget();
};
