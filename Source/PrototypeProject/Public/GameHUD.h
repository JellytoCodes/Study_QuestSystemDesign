// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameHUD.generated.h"

class UQuestUIWidget;
class UTimeManagerWidget;
class UGameSaveLoad;

UCLASS()
class PROTOTYPEPROJECT_API AGameHUD : public AHUD
{
	GENERATED_BODY()

public :
	AGameHUD();

	void CompletedWidget(FName QuestID);
	void StartedWidget(FName QuestID);
	void SaveLoadViewWidget();

protected :
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	//����Ʈ ���� / �Ϸ� UI
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UQuestUIWidget> QuestWidgetUI;
	UQuestUIWidget* QuestWidget;

	//Ÿ�̸� UI
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UTimeManagerWidget> TimerWidgetUI;
	UTimeManagerWidget* TimerWidget;

	class UTimeManager* Timer;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UGameSaveLoad> SaveLoadWidgetUI;
	UGameSaveLoad* SaveLoadWidget;

	UFUNCTION()
	void GameClear();

	bool bIsSaveLoad = false;
};
