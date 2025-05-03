// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class PROTOTYPEPROJECT_API AGameHUD : public AHUD
{
	GENERATED_BODY()

public :
	AGameHUD();

	void CompletedWidget(FName QuestID);
	void StartedWidget(FName QuestID);

protected :
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UQuestUIWidget> QuestWidgetUI;

	UQuestUIWidget* QuestWidget;

	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UTimeManagerWidget> TimerWidgetUI;

	UTimeManagerWidget* TimerWidget;

	class UTimeManager* Timer;

	UFUNCTION()
	void GameClear();
};
