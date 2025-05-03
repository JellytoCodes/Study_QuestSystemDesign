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
	virtual void NativeConstruct() override;

	void TextSet();

protected :
	UFUNCTION()
	void OnQuestUpdated(FName QuestID);

	void OnQuestAlram(FName QuestID);

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* QuestStatusText;
};
