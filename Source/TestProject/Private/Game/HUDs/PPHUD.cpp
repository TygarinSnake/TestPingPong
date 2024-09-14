#include "Game/HUDs/PPHUD.h"

#include "Game/Widgets/ScoreboardUserWidget.h"

void APPHUD::BeginPlay()
{
    Super::BeginPlay();

    ScoreboardWidget = CreateWidget<UScoreboardUserWidget>(GetOwningPlayerController(), ScoreboardWidgetClass);
    check(ScoreboardWidget);  

    ScoreboardWidget->AddToViewport();
}

void APPHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    check(ScoreboardWidget);
    ScoreboardWidget->RemoveFromParent();
}

FORCEINLINE void APPHUD::RefreshScoreboard(const TMap<FString, int32>& NewScoreMap)
{
    ScoreboardWidget->RefreshScoreboard(NewScoreMap);
}
