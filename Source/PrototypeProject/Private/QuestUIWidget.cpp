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
	UE_LOG(LogTemp, Log, TEXT("OnQuestUpdated!"));
	FQueuedQuestNotification NewNotify;
	NewNotify.QuestID = QuestID;
	NewNotify.bIsCompleted = bIsCompleted;
	QuestNotificationQueue.Enqueue(NewNotify);

	if(!bIsPlaying)
	{
		PlayNextNotification();
	}

}

void UQuestUIWidget::OnFadeOutFinished()
{
	SetVisibility(ESlateVisibility::Hidden);
	
	bIsPlaying = false;

	PlayNextNotification();
}

void UQuestUIWidget::TextSet()
{
	QuestStatusText->SetText(FText::FromString(FString::Printf(TEXT("Quest Filed!"))));
}

void UQuestUIWidget::PlayFadeAnimation()
{
	if(FadeInOut)
	{
		SetVisibility(ESlateVisibility::Visible);
		StopAnimation(FadeInOut);
		PlayAnimation(FadeInOut, 0.f, 1);
	}
}

void UQuestUIWidget::PlayNextNotification()
{
	if(bIsPlaying) return;

	FQueuedQuestNotification Notify;
	if(QuestNotificationQueue.Dequeue(Notify))
	{
		if(QuestStatusText)
		{
			UE_LOG(LogTemp, Warning, TEXT("Notify.bIsCompleted : %d"), Notify.bIsCompleted);
			//퀘스트 완료 여부에 따라 메시지 출력
			FString Msg = Notify.bIsCompleted
			? FString::Printf(TEXT("%s Quest Completed!"), *Notify.QuestID.ToString())
			: FString::Printf(TEXT("%s Quest Started!"), *Notify.QuestID.ToString());
			QuestStatusText->SetText(FText::FromString(Msg));
		}

		//애니메이션 출력

		SetVisibility(ESlateVisibility::Visible);
		StopAnimation(FadeInOut);
		PlayAnimation(FadeInOut, 0.f, 1);
		bIsPlaying = true;
	}
}
