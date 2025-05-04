// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPEPROJECT_API UQuestUIWidget : public UUserWidget
{
	GENERATED_BODY()


public :
	void TextSet();

	UFUNCTION(BlueprintCallable)
	void PlayFadeAnimation();

	UFUNCTION()
	void OnQuestUpdated(FName QuestID, bool bIsCompleted);

protected :
	virtual void NativeConstruct() override;



	UPROPERTY(meta = (BindWidget))
	class UTextBlock* QuestStatusText;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* FadeInOut;

	UFUNCTION()
	void OnFadeOutFinished();

	FWidgetAnimationDynamicEvent EndDelegate;
};
