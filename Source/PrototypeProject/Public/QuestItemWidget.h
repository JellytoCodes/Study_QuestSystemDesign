// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestItemWidget.generated.h"

class UTextBlock;

UCLASS()
class PROTOTYPEPROJECT_API UQuestItemWidget : public UUserWidget
{
	GENERATED_BODY()

public :
	void SetQuestInfo(const FText& Title, const FText& Description, bool bIsCompleted);

protected :
	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuestTitle;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuestDescription;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* QuestState;

};
