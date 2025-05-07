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

	//����Ʈ ������Ʈ
	UFUNCTION()
	void OnQuestUpdated(FName QuestID, bool bIsCompleted);

	//Ÿ�� ������ ���� ����Ʈ ���� ����� (TEST)
	void TextSet();

	//����Ʈ ����Ʈ ����
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
