// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestNotifyWidget.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UQuestNotifyWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	EndDelegate.BindDynamic(this, &UQuestNotifyWidget::OnAnimationFinish);

	if(FadeInOut)
	{
		BindToAnimationFinished(FadeInOut, EndDelegate);
	}
}

void UQuestNotifyWidget::ShowNotification(const FText &Message)
{
	if(NotifyText)
	{
		NotifyText->SetText(Message);
	}
	SetVisibility(ESlateVisibility::Visible);
	PlayAnimation(FadeInOut, 0.f, 1);
}

void UQuestNotifyWidget::OnAnimationFinish()
{
	RemoveFromParent();
}
