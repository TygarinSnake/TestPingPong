#include "Game/Widgets/ScoreboardUserWidget.h"

#include "Components/ScrollBox.h"

#include "Game/Widgets/ScoreLineUserWidget.h"

void UScoreboardUserWidget::RefreshScoreboard(const TMap<FString, int32>& NewScoreMap)
{
    check(ScrollBox_Scoreboard);
    ScrollBox_Scoreboard->ClearChildren();

    for (const TPair<FString, int32>& Pair : NewScoreMap)
    {        
        UScoreLineUserWidget* NewItem = CreateWidget<UScoreLineUserWidget>(GetOwningPlayer(), LineWidgetClass);
        NewItem->SetInfo(Pair.Key, Pair.Value);
        ScrollBox_Scoreboard->AddChild(NewItem);
    }
}
