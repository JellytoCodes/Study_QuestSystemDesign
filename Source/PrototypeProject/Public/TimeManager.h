// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TimeManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDefenseTimeCompleted);

UCLASS()
class PROTOTYPEPROJECT_API UTimeManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public :
	void StartDefensePhase();
	void OnDefenseComplete();

	void PauseDefensePhase();
	void ResumeDefensePhase();

	bool IsPaused() const { return bIsPaused; }

	float GetRemainingDefenseTime() const;

	FOnDefenseTimeCompleted OnDefenseTimeCompleted;

private :
	FTimerHandle DefenseTimerHandle;

	float DefenseTimer = 120.f;
	float DefenseStartTimer = 0.f;
	float RemainingTime = 0;
	bool bIsPaused = false;
};
