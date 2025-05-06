// Fill out your copyright notice in the Description page of Project Settings.

#include "UPrototypeQuestSubsystem.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "QuestSaveGame.h"

void UUPrototypeQuestSubsystem::Initialize(FSubsystemCollectionBase &Collection)
{
	Super::Initialize(Collection);

	UDataTable* LoadedTable = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, TEXT("/Game/Blueprints/DT_QuestData.DT_QuestData")));
	if(LoadedTable)
	{
		UE_LOG(LogTemp, Log, TEXT("QuestSubsystem DataTable Initialized"));
		QuestDataTable = LoadedTable;
	}
	TArray<FName> RowNames = QuestDataTable->GetRowNames();
	for(const FName& RowName : RowNames)
	{
		if(!QuestStateMap.Contains(RowName))
		{
			FQuestState InitialState;
			InitialState.bIsStarted = false;
			InitialState.bIsCompleted = false;
			QuestStateMap.Add(RowName, InitialState);
		}
	}
}

void UUPrototypeQuestSubsystem::Deinitialize()
{
	Super::Deinitialize();
	QuestStateMap.Empty();
}

void UUPrototypeQuestSubsystem::SetQuestStarted(FName QuestID)
{
	if(FQuestState* State = QuestStateMap.Find(QuestID))
	{
		if(!State->bIsStarted)
		{
			State->bIsStarted = true;
			OnQuestUpdated.Broadcast(QuestID, false);
			UE_LOG(LogTemp, Log, TEXT("bIsStarted Set : %d"), State->bIsStarted);
		}
	}
}

void UUPrototypeQuestSubsystem::SetQuestCompleted(FName QuestID)
{
	if(FQuestState* State = QuestStateMap.Find(QuestID))
	{
		if(State->bIsStarted && !State->bIsCompleted)
		{
			UE_LOG(LogTemp, Warning, TEXT("bIsCompleted"));
			State->bIsCompleted = true;
			OnQuestUpdated.Broadcast(QuestID, true);
		}
	}
}

bool UUPrototypeQuestSubsystem::IsQuestStarted(FName QuestID) const
{
	if(const FQuestState* State = QuestStateMap.Find(QuestID))
	{
		return State->bIsStarted;
	}
	return false;
}

bool UUPrototypeQuestSubsystem::IsQuestCompleted(FName QuestID) const
{
	if(const FQuestState* State = QuestStateMap.Find(QuestID))
	{
		return State->bIsCompleted;
	}
	return false;
}

const FQuestData *UUPrototypeQuestSubsystem::GetQuestData(FName QuestID)
{
	if(!QuestDataTable) return nullptr;
	return QuestDataTable->FindRow<FQuestData>(QuestID, TEXT("QuestSubsystemLookUp"));
}

bool UUPrototypeQuestSubsystem::TryCompleteQuest(FName ItemID)
{
	for (const auto& Pair : QuestStateMap)
	{
		const FName& QuestID = Pair.Key;
		const FQuestState& State = Pair.Value;

		if (!State.bIsStarted || State.bIsCompleted)
			continue;

		const FQuestData* QuestData = GetQuestData(QuestID);
		if (!QuestData) continue;

		// 아이템 기반 퀘스트에 따른 완료 조건
		if (QuestData->ConditionType == EQuestConditionType::PickupItem && QuestData->RequiredItems.Contains(ItemID))
		{
			SetQuestCompleted(QuestID);
			UE_LOG(LogTemp, Log, TEXT("Quest '%s' completed by picking up item '%s'"), *QuestID.ToString(), *ItemID.ToString());
			return true;
		}
	}
	return false;
}

void UUPrototypeQuestSubsystem::SaveQuestProgress(const FString& SlotName)
{
	UQuestSaveGame* SaveData = Cast<UQuestSaveGame>(UGameplayStatics::CreateSaveGameObject(UQuestSaveGame::StaticClass()));
	if(!SaveData) return;

	//퀘스트 상태 복사
	SaveData->SavedQuestStates = QuestStateMap;

	//퀘스트 상태 저장
	if(UGameplayStatics::SaveGameToSlot(SaveData, SlotName, 0))
	{
		UE_LOG(LogTemp, Log, TEXT("Quest progress saved to slot"));
	}
}

void UUPrototypeQuestSubsystem::LoadQuestProgress(const FString& SlotName)
{
	USaveGame* Loaded = UGameplayStatics::LoadGameFromSlot(SlotName, 0);
	if(!Loaded) return;

	if(UQuestSaveGame* SaveData = Cast<UQuestSaveGame>(Loaded))
	{
		QuestStateMap = SaveData->SavedQuestStates;
		UE_LOG(LogTemp, Log, TEXT("Quest progress loaded from slot"));
	}
}
