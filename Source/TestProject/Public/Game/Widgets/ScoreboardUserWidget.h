#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreboardUserWidget.generated.h"

class UTextBlock;

UCLASS(Abstract)
class TESTPROJECT_API UScoreboardUserWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> TextBlock_TopScore;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> TextBlock_BottomScore;

public:
    void NativeConstruct();
};
