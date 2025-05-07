// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestItemWidget.h"
#include "Components/TextBlock.h"

void UQuestItemWidget::SetQuestInfo(const FText &Title, const FText &Description, bool bIsCompleted)
{
	if(QuestTitle) QuestTitle->SetText(Title);
	if(QuestDescription) QuestDescription->SetText(Description);
	if(QuestState) QuestState->SetText(bIsCompleted ? FText::FromString(TEXT("Completed")) : FText::FromString(TEXT("in Progress")));
}
