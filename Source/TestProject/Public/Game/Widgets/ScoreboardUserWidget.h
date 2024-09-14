#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreboardUserWidget.generated.h"

class UScrollBox;
class UScoreLineUserWidget;

UCLASS(Abstract)
class TESTPROJECT_API UScoreboardUserWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UScrollBox> ScrollBox_Scoreboard;

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<UScoreLineUserWidget> LineWidgetClass;

public:
    void RefreshScoreboard(const TMap<FString, int32>& NewScoreMap);
};
