// Fill out your copyright notice in the Description page of Project Settings.

#include "UPrototypeQuestSubsystem.h"

void UUPrototypeQuestSubsystem::Initialize(FSubsystemCollectionBase &Collection)
{
	Super::Initialize(Collection);

	UE_LOG(LogTemp, Log, TEXT("QuestSubsystem Initialized"));
}

void UUPrototypeQuestSubsystem::Deinitialize()
{
	Super::Deinitialize();
	QuestStateMap.Empty();
}

void UUPrototypeQuestSubsystem::SetQuestState(FName QuestID, bool bCompleted)
{
	if(QuestList.IsValidIndex(CurrentQuestIndex) && QuestList[CurrentQuestIndex] == QuestID)
	{
		QuestStateMap.Add(QuestID, bCompleted);
		UE_LOG(LogTemp, Log, TEXT("Quest Clear : %s"), *QuestID.ToString());
		OnQuestUpdated.Broadcast(QuestID);
		AdvanceToNextQuest();
	}
}

bool UUPrototypeQuestSubsystem::IsQuestCompleted(FName QuestID) const
{
	if(const bool* bState = QuestStateMap.Find(QuestID))
	{
		return *bState;
	}
	return false;
}

FName UUPrototypeQuestSubsystem::GetCurrentQuestID() const
{
	if(QuestList.IsValidIndex(CurrentQuestIndex))
	{
		UE_LOG(LogTemp, Log, TEXT("CurrentQuestIndex : %d"), CurrentQuestIndex);
		return QuestList[CurrentQuestIndex];
	}
	return NAME_None;
}

void UUPrototypeQuestSubsystem::AdvanceToNextQuest()
{
	//OnQuestUpdated.Broadcast(GetCurrentQuestID());
	CurrentQuestIndex++;
}
