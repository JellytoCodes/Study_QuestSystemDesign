// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestUIWidget.h"
#include "UPrototypeQuestSubsystem.h"
#include "Components/TextBlock.h"

void UQuestUIWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if(UUPrototypeQuestSubsystem* Sub = GetGameInstance()->GetSubsystem<UUPrototypeQuestSubsystem>())
	{
		Sub->OnQuestUpdated.AddDynamic(this, &UQuestUIWidget::OnQuestUpdated);
	}
}

void UQuestUIWidget::OnQuestUpdated(FName QuestID)
{
	if(QuestStatusText)
	{
		UE_LOG(LogTemp, Warning, TEXT("Quest Completed: %s"), *QuestID.ToString());
		QuestStatusText->SetText(FText::FromString(FString::Printf(TEXT("%s Quest Completed!"), *QuestID.ToString())));
	}
}

void UQuestUIWidget::OnQuestAlram(FName QuestID)
{
	if(QuestStatusText)
	{
		QuestStatusText->SetText(FText::FromString(FString::Printf(TEXT("%s Quest Start!"), *QuestID.ToString())));
	}
}

void UQuestUIWidget::TextSet()
{
	QuestStatusText->SetText(FText::FromString(FString::Printf(TEXT("Quest Filed!"))));
}
