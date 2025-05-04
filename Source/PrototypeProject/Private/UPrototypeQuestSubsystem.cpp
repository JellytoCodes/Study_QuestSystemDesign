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

void UUPrototypeQuestSubsystem::SetQuestState(FName QuestID, bool bStart, bool bCompleted)
{
	FQuestData& Quest = QuestMap.FindOrAdd(QuestID);
	if(bStart) Quest.bIsStarted = true;
	if(bCompleted) Quest.bIsCompleted = true;

	OnQuestUpdated.Broadcast(QuestID, Quest.bIsCompleted);
}

bool UUPrototypeQuestSubsystem::IsQuestStarted(FName QuestID) const
{
	if(const FQuestData* Quest = QuestMap.Find(QuestID))
	{
		return Quest->bIsStarted;
	}
	return false;
}

bool UUPrototypeQuestSubsystem::IsQuestCompleted(FName QuestID) const
{
	if(const FQuestData* Quest = QuestMap.Find(QuestID))
	{
		return Quest->bIsCompleted;
	}
	return false;
}

FName UUPrototypeQuestSubsystem::GetCurrentQuestID(bool bIsCompleted) const
{
	for (const TPair<FName, FQuestData>& Elem : QuestMap)
	{
		if(bIsCompleted && Elem.Value.bIsCompleted)
		{
			return Elem.Key;
		}
		else if(!bIsCompleted && Elem.Value.bIsStarted && !Elem.Value.bIsCompleted)
		{
			return Elem.Key;
		}
	}
	return NAME_None;
}