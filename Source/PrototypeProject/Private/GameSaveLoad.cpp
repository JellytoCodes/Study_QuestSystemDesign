// Fill out your copyright notice in the Description page of Project Settings.

#include "GameSaveLoad.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "UPrototypeQuestSubsystem.h"

void UGameSaveLoad::NativeConstruct()
{
	Super::NativeConstruct();

	SlotButton_1->OnClicked.AddDynamic(this, &UGameSaveLoad::OnClickSlot1);
	SlotButton_2->OnClicked.AddDynamic(this, &UGameSaveLoad::OnClickSlot2);

	SlotText_1->SetText(UGameplayStatics::DoesSaveGameExist("QuestSaveSlot1", 0) ? FText::FromString("Saved") : FText::FromString("No Data"));
	SlotText_2->SetText(UGameplayStatics::DoesSaveGameExist("QuestSaveSlot2", 0) ? FText::FromString("Saved") : FText::FromString("No Data"));

	DeleteButton_1->OnClicked.AddDynamic(this, &UGameSaveLoad::OnClickDelete1);
	DeleteButton_2->OnClicked.AddDynamic(this, &UGameSaveLoad::OnClickDelete2);
}

void UGameSaveLoad::OnClickSlot1()
{
	if(UGameplayStatics::DoesSaveGameExist("QuestSaveSlot1", 0)) LoadFromSlot(1);
	else SaveToSlot(1);
}

void UGameSaveLoad::OnClickDelete1()
{
	DeleteSlot(1);
}

void UGameSaveLoad::OnClickSlot2()
{
	if(UGameplayStatics::DoesSaveGameExist("QuestSaveSlot2", 0)) LoadFromSlot(2);
	else SaveToSlot(2);
}

void UGameSaveLoad::OnClickDelete2()
{
	DeleteSlot(2);
}

void UGameSaveLoad::SaveToSlot(int32 SlotIndex)
{
	FString SlotName = FString::Printf(TEXT("QuestSaveSlot%d"), SlotIndex);
	if(UUPrototypeQuestSubsystem* Subsystem = GetGameInstance()->GetSubsystem<UUPrototypeQuestSubsystem>())
	{
		Subsystem->SaveQuestProgress(SlotName);
	}

	if (SlotIndex == 1) SlotText_1->SetText(FText::FromString("Saved"));
	if (SlotIndex == 2) SlotText_2->SetText(FText::FromString("Saved"));
}

void UGameSaveLoad::LoadFromSlot(int32 SlotIndex)
{
	FString SlotName = FString::Printf(TEXT("QuestSaveSlot%d"), SlotIndex);
	if(UUPrototypeQuestSubsystem* Subsystem = GetGameInstance()->GetSubsystem<UUPrototypeQuestSubsystem>())
	{
		Subsystem->LoadQuestProgress(SlotName);
	}
}

void UGameSaveLoad::DeleteSlot(int32 SlotIndex)
{
	FString SlotName = FString::Printf(TEXT("QuestSaveSlot%d"), SlotIndex);
	if(UGameplayStatics::DeleteGameInSlot(SlotName, 0))
	{
		UE_LOG(LogTemp, Log, TEXT("Slot%d deleted."), SlotIndex);

		if(SlotIndex == 1) SlotText_1->SetText(FText::FromString("No Data"));
		if(SlotIndex == 2) SlotText_2->SetText(FText::FromString("No Data"));
	}
}
