// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "QuestDataDefs.h"
#include "QuestNameDefs.h"
#include "UPrototypeQuestSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnQuestUpdated, FName, QuestID, bool, bCompleted);

USTRUCT(BlueprintType)
struct FQuestState
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	bool bIsStarted = false;

	UPROPERTY(BlueprintReadWrite)
	bool bIsCompleted = false;
};

UCLASS()
class PROTOTYPEPROJECT_API UUPrototypeQuestSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public :
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	//퀘스트 시작 / 완료 설정 및 Broadcast
	void SetQuestStarted(FName QuestID);
	void SetQuestCompleted(FName QuestID);

	//현재 퀘스트 시작 / 완료 여부 반환
	bool IsQuestStarted(FName QuestID) const;
	bool IsQuestCompleted(FName QuestID) const;

	UPROPERTY(BlueprintAssignable)
	FOnQuestUpdated OnQuestUpdated;

	//퀘스트 DataTable Import
	const FQuestData* GetQuestData(FName QuestID);

	//조건에 따른 퀘스트 완료 처리
	bool TryCompleteQuest(FName ItemID);

	//퀘스트 Save / Load
	UFUNCTION(BlueprintCallable)
	void SaveQuestProgress(const FString& SlotName);

	UFUNCTION(BlueprintCallable)
	void LoadQuestProgress(const FString& SlotName);

private :
	UPROPERTY()
	class UDataTable* QuestDataTable;

	UPROPERTY(EditDefaultsOnly, Category = "Quest")
	TMap<FName, FQuestState> QuestStateMap;
};