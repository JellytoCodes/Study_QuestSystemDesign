// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestUIWidget.generated.h"

class UTextBlock;
class UVerticalBox;
class UQuestItemWidget;
class UQuestNotifyWidget;

UCLASS()
class PROTOTYPEPROJECT_API UQuestUIWidget : public UUserWidget
{
	GENERATED_BODY()

public :
	virtual void NativeConstruct() override;

	//퀘스트 업데이트
	UFUNCTION()
	void OnQuestUpdated(FName QuestID, bool bIsCompleted);

	//타임 오버에 따른 퀘스트 실패 재생용 (TEST)
	void TextSet();

	//퀘스트 리스트 갱신
	void RefreshQuestList();

	UFUNCTION()
	void QuestListUpdated(FName UpdatedQuestID);

protected :
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* VerticalBox_QuestList;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UQuestItemWidget> QuestItemWidgetClass;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UQuestNotifyWidget> QuestNotifyWidgetClass;
};
