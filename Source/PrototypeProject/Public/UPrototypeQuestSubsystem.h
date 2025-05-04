// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UPrototypeQuestSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnQuestUpdated, FName, QuestID, bool, bCompleted);

USTRUCT()
struct FQuestData
{
	GENERATED_BODY()

	bool bIsStarted = false;
	bool bIsCompleted = false;
};

UCLASS()
class PROTOTYPEPROJECT_API UUPrototypeQuestSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public :
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void SetQuestState(FName QuestID, bool bStart, bool bCompleted);
	bool IsQuestStarted(FName QuestID) const;
	bool IsQuestCompleted(FName QuestID) const;

	UPROPERTY(BlueprintAssignable)
	FOnQuestUpdated OnQuestUpdated;

	FName GetCurrentQuestID(bool bIsCompleted) const;

private :
	TMap<FName, bool> QuestStateMap;
	TMap<FName, FQuestData> QuestMap;
};