#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreLineUserWidget.generated.h"

class UTextBlock;

UCLASS(Abstract)
class TESTPROJECT_API UScoreLineUserWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> TextBlock_Name;
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> TextBlock_Score;

public:
    void SetInfo(FString Name, int32 Score);
};
