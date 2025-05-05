// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestUIWidget.generated.h"

USTRUCT()
struct FQueuedQuestNotification
{
	GENERATED_BODY()

	UPROPERTY()
	FName QuestID;

	UPROPERTY()
	bool bIsCompleted;
};

UCLASS()
class PROTOTYPEPROJECT_API UQuestUIWidget : public UUserWidget
{
	GENERATED_BODY()

public :
	virtual void NativeConstruct() override;

	//퀘스트 업데이트
	UFUNCTION()
	void OnQuestUpdated(FName QuestID, bool bIsCompleted);

	//테스트용 수동 재생
	void PlayFadeAnimation();

	//큐에서 다음 알림 재생
	void PlayNextNotification();

	//타임 오버에 따른 퀘스트 실패 재생용 (TEST)
	void TextSet();


protected :
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* QuestStatusText;

	//UserWidget Animation(FadeInOut)
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* FadeInOut;

	UFUNCTION()
	void OnFadeOutFinished();

private :
	//큐 구조
	TQueue<FQueuedQuestNotification> QuestNotificationQueue;

	//현재 애니메이션 진행 여부
	bool bIsPlaying = false;

	//애니메이션 종료 알림용 Delegate
	FWidgetAnimationDynamicEvent EndDelegate;
};
