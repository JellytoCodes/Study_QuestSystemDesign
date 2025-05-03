// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UPrototypeQuestSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestUpdated, FName, QuestID);

UCLASS()
class PROTOTYPEPROJECT_API UUPrototypeQuestSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public :
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void SetQuestState(FName QuestID, bool bCompleted);
	bool IsQuestCompleted(FName QuestID) const;

	UPROPERTY(BlueprintAssignable)
	FOnQuestUpdated OnQuestUpdated;

	FName GetCurrentQuestID() const;
	void AdvanceToNextQuest();

private :
	TMap<FName, bool> QuestStateMap;
	TArray<FName> QuestList
	{
		"EnteredArea01",
		"EnteredArea02",
	};

	int32 CurrentQuestIndex = 0;
};