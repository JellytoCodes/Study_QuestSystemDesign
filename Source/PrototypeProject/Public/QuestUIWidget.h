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

	//����Ʈ ������Ʈ
	UFUNCTION()
	void OnQuestUpdated(FName QuestID, bool bIsCompleted);

	//�׽�Ʈ�� ���� ���
	void PlayFadeAnimation();

	//ť���� ���� �˸� ���
	void PlayNextNotification();

	//Ÿ�� ������ ���� ����Ʈ ���� ����� (TEST)
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
	//ť ����
	TQueue<FQueuedQuestNotification> QuestNotificationQueue;

	//���� �ִϸ��̼� ���� ����
	bool bIsPlaying = false;

	//�ִϸ��̼� ���� �˸��� Delegate
	FWidgetAnimationDynamicEvent EndDelegate;
};
