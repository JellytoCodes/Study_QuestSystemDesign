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

	//����Ʈ ���� / �Ϸ� ���� �� Broadcast
	void SetQuestStarted(FName QuestID);
	void SetQuestCompleted(FName QuestID);

	//���� ����Ʈ ���� / �Ϸ� ���� ��ȯ
	bool IsQuestStarted(FName QuestID) const;
	bool IsQuestCompleted(FName QuestID) const;

	UPROPERTY(BlueprintAssignable)
	FOnQuestUpdated OnQuestUpdated;

	//����Ʈ DataTable Import
	const FQuestData* GetQuestData(FName QuestID);

	//���ǿ� ���� ����Ʈ �Ϸ� ó��
	bool TryCompleteQuest(FName ItemID);

	//����Ʈ Save / Load
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