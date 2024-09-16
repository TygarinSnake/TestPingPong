#include "Game/HUDs/PPHUD.h"

#include "Net/UnrealNetwork.h"

#include "Game/Widgets/ScoreboardUserWidget.h"

void APPHUD::BeginPlay()
{
    Super::BeginPlay();

    ScoreboardWidget = CreateWidget<UScoreboardUserWidget>(GetOwningPlayerController(), ScoreboardWidgetClass);
    WaitConnectionWidget = CreateWidget<UUserWidget>(GetOwningPlayerController(), WaitConnectionWidgetClass);
    check(ScoreboardWidget);
    check(WaitConnectionWidget);

    ScoreboardWidget->AddToViewport();
    WaitConnectionWidget->AddToViewport();

    HideScoreboardWidget();
    HideWaitConnectionWidget();
}

FORCEINLINE void APPHUD::HideScoreboardWidget()
{
    check(ScoreboardWidget);
    ScoreboardWidget->SetVisibility(ESlateVisibility::Hidden);
}

FORCEINLINE void APPHUD::ShowWaitConnectionWidget()
{
    check(WaitConnectionWidget);
    WaitConnectionWidget->SetVisibility(ESlateVisibility::Visible);
}

void APPHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    check(ScoreboardWidget);
    check(WaitConnectionWidget);
    ScoreboardWidget->RemoveFromParent();
    WaitConnectionWidget->RemoveFromParent();
}

FORCEINLINE void APPHUD::SetScoreboardData(const TMap<FString, int32>& NewScoreMap)
{
    check(ScoreboardWidget);
    ScoreboardWidget->RefreshScoreboard(NewScoreMap);
}

FORCEINLINE void APPHUD::ShowScoreboardWidget()
{
    check(ScoreboardWidget);
    ScoreboardWidget->SetVisibility(ESlateVisibility::Visible);
}

void APPHUD::HideWaitConnectionWidget()
{
    check(WaitConnectionWidget);
    WaitConnectionWidget->SetVisibility(ESlateVisibility::Hidden);
}

void APPHUD::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(APPHUD, ScoreboardWidget);
    DOREPLIFETIME(APPHUD, WaitConnectionWidget);
}
