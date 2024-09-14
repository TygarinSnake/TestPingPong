#include "Game/Widgets/ScoreLineUserWidget.h"

#include "Components/TextBlock.h"

void UScoreLineUserWidget::SetInfo(FString Name, int32 Score)
{
    check(TextBlock_Name);
    check(TextBlock_Score);

    TextBlock_Name->SetText(FText::FromString(Name));
    TextBlock_Score->SetText(FText::AsNumber(Score));
}
