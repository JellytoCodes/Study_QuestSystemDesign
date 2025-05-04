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

	EndDelegate.BindDynamic(this, &UQuestUIWidget::OnFadeOutFinished);

	if(FadeInOut)
	{
		BindToAnimationFinished(FadeInOut, EndDelegate);
	}
}

void UQuestUIWidget::OnQuestUpdated(FName QuestID, bool bIsCompleted)
{
	if(QuestStatusText)
	{
		if(bIsCompleted)
		{
			QuestStatusText->SetText(FText::FromString(FString::Printf(TEXT("%s Quest Completed!"), *QuestID.ToString())));
		}
		else
		{
			QuestStatusText->SetText(FText::FromString(FString::Printf(TEXT("%s Quest Started!"), *QuestID.ToString())));
		}
	}
}

void UQuestUIWidget::OnFadeOutFinished()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UQuestUIWidget::TextSet()
{
	QuestStatusText->SetText(FText::FromString(FString::Printf(TEXT("Quest Filed!"))));
}

void UQuestUIWidget::PlayFadeAnimation()
{
	if(FadeInOut)
	{
		PlayAnimation(FadeInOut);
	}
}
