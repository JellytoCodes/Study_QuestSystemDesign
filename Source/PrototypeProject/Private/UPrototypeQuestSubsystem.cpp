// Fill out your copyright notice in the Description page of Project Settings.

#include "UPrototypeQuestSubsystem.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "GameHUD.h"
#include "QuestNameDefs.h"

void UUPrototypeQuestSubsystem::Initialize(FSubsystemCollectionBase &Collection)
{
	Super::Initialize(Collection);

	UE_LOG(LogTemp, Log, TEXT("QuestSubsystem Initialized"));
}

void UUPrototypeQuestSubsystem::Deinitialize()
{
	Super::Deinitialize();
	QuestMap.Empty();
}

void UUPrototypeQuestSubsystem::SetQuestStarted(FName QuestID, FQuestData AddData)
{
	EQuestName QuestName = FQuestNameHelper::FromFName(QuestID);
	if(FQuestData* QuestData = QuestMap.Find(QuestID))
	{
		if(!QuestData->bIsStarted)
		{
			*QuestData = AddData;
			QuestData->bIsStarted = true;
			OnQuestUpdated.Broadcast(QuestID, false);
		}
	}
}

void UUPrototypeQuestSubsystem::SetQuestCompleted(FName QuestID)
{
	if(FQuestData* QuestData = QuestMap.Find(QuestID))
	{
		if(QuestData->bIsStarted && !QuestData->bIsCompleted)
		{
			UE_LOG(LogTemp, Warning, TEXT("bIsCompleted"));
			QuestData->bIsCompleted = true;
			OnQuestUpdated.Broadcast(QuestID, true);
		}
	}
}

bool UUPrototypeQuestSubsystem::IsQuestStarted(FName QuestID) const
{
	if(const FQuestData* QuestData = QuestMap.Find(QuestID))
	{
		return QuestData->bIsStarted;
	}
	return false;
}

bool UUPrototypeQuestSubsystem::IsQuestCompleted(FName QuestID) const
{
	if(const FQuestData* QuestData = QuestMap.Find(QuestID))
	{
		return QuestData->bIsCompleted;
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

void UUPrototypeQuestSubsystem::RegisterQuest(FName QuestID, EQuestTriggerType Type)
{
	if(!QuestMap.Contains(QuestID))
	{
		FQuestData NewData;
		NewData.TriggerType = Type;
		QuestMap.Add(QuestID, NewData);
	}
}

EQuestTriggerType UUPrototypeQuestSubsystem::GetQuestTriggerType(FName QuestID) const
{
	if(const FQuestData* Quest = QuestMap.Find(QuestID))
	{
		return Quest->TriggerType;
	}
	return EQuestTriggerType::None;
}

EQuestConditionType UUPrototypeQuestSubsystem::GetQuestConditionType(FName QuestID) const
{
	if(const FQuestData* Quest = QuestMap.Find(QuestID))
	{
		UE_LOG(LogTemp, Warning, TEXT("Get ConditionType"));
		return Quest->ConditionType;
	}
	return EQuestConditionType::None;
}

bool UUPrototypeQuestSubsystem::TryCompleteQuest(FName QuestID, EQuestConditionType CompletedType, FName Value)
{
	if(FQuestData* Quest = QuestMap.Find(QuestID))
	{
		if(Quest->bIsStarted && !Quest->bIsCompleted && Quest->ConditionType == CompletedType &&
		(Quest->RequiredValue.IsNone() || Quest->RequiredValue == Value))
		{
			UE_LOG(LogTemp, Warning, TEXT("TryCompleteQuest!"));
			SetQuestCompleted(QuestID);
			return true;
		}
	}
	return false;
}

