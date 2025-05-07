// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestNotifyWidget.generated.h"

class UTextBlock;
class UWidgetAnimation;

UCLASS()
class PROTOTYPEPROJECT_API UQuestNotifyWidget : public UUserWidget
{
	GENERATED_BODY()

public :
	UFUNCTION()
	void ShowNotification(const FText& Message);

	UFUNCTION()
	void OnAnimationFinish();

protected :
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* NotifyText;

	//UserWidget Animation(FadeInOut)
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* FadeInOut;

private :
	FTimerHandle RemoveTimerHandle;

	//애니메이션 종료 알림용 Delegate
	FWidgetAnimationDynamicEvent EndDelegate;
};
