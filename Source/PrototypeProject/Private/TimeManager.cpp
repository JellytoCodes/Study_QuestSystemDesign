// Fill out your copyright notice in the Description page of Project Settings.


#include "TimeManager.h"

void UTimeManager::StartDefensePhase()
{
	DefenseStartTimer = GetWorld()->GetTimeSeconds();
	RemainingTime = DefenseTimer;
	bIsPaused = false;

	GetWorld()->GetTimerManager().SetTimer(DefenseTimerHandle, this, &UTimeManager::OnDefenseComplete,  DefenseTimer, false);
}

void UTimeManager::OnDefenseComplete()
{
	OnDefenseTimeCompleted.Broadcast();
}

void UTimeManager::PauseDefensePhase()
{
	
	if(GetWorld()->GetTimerManager().IsTimerActive(DefenseTimerHandle))
	{
		RemainingTime = GetWorld()->GetTimerManager().GetTimerRemaining(DefenseTimerHandle);
		GetWorld()->GetTimerManager().ClearTimer(DefenseTimerHandle);
		bIsPaused = true;
		
		UE_LOG(LogTemp, Log, TEXT("Timer Paused. Remaining : %.2f"), RemainingTime);
	}
}

void UTimeManager::ResumeDefensePhase()
{
	if(bIsPaused && RemainingTime > 0.f)
	{
		DefenseStartTimer = GetWorld()->GetTimeSeconds();
		GetWorld()->GetTimerManager().SetTimer(DefenseTimerHandle, this, &UTimeManager::OnDefenseComplete, RemainingTime, false);
		bIsPaused = false;

		UE_LOG(LogTemp, Log, TEXT("Timer Resume. Remaining : %.2f"), RemainingTime);
	}
}

float UTimeManager::GetRemainingDefenseTime() const
{
	if(bIsPaused)
	{
		return RemainingTime;
	}

	else
	{
		float Elapsed = GetWorld()->GetTimeSeconds() - DefenseStartTimer;
		return FMath::Max(RemainingTime - Elapsed, 0.f);
	}
}