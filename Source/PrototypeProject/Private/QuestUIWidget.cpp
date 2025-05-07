// Fill out your copyright notice in the Description page of Project Settings.


#include "QuestUIWidget.h"
#include "UPrototypeQuestSubsystem.h"
#include "QuestItemWidget.h"
#include "QuestNotifyWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"

void UQuestUIWidget::NativeConstruct()
{
	Super::NativeConstruct();

	//퀘스트 리스트 미리 할당
	RefreshQuestList();

	if(auto Sub = GetGameInstance()->GetSubsystem<UUPrototypeQuestSubsystem>())
	{
		Sub->OnQuestUpdated.AddDynamic(this, &UQuestUIWidget::OnQuestUpdated);
		Sub->OnQuestUpdatedOne.AddDynamic(this, &UQuestUIWidget::QuestListUpdated);
	}
}

void UQuestUIWidget::OnQuestUpdated(FName QuestID, bool bIsCompleted)
{
	if (auto Sub = GetGameInstance()->GetSubsystem<UUPrototypeQuestSubsystem>())
	{
		const FQuestData* QuestData = Sub->GetQuestData(QuestID);
		if (!QuestData) return;

		FText Msg = bIsCompleted
			? FText::Format(NSLOCTEXT("Quest", "CompletedMsg", "{0} Quest Completed!"), QuestData->QuestTitle)
			: FText::Format(NSLOCTEXT("Quest", "StartedMsg", "{0} Quest Started!"), QuestData->QuestTitle);

		if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
		{
			if (QuestNotifyWidgetClass)
			{
				auto NotifyWidget = CreateWidget<UQuestNotifyWidget>(PC, QuestNotifyWidgetClass);
				if (NotifyWidget)
				{
					NotifyWidget->ShowNotification(Msg);
					NotifyWidget->AddToViewport();
				}
			}
		}
	}
}

void UQuestUIWidget::TextSet()
{
	//QuestStatusText->SetText(FText::FromString(FString::Printf(TEXT("Quest Filed!"))));
}

void UQuestUIWidget::RefreshQuestList()
{
	if(!VerticalBox_QuestList || !QuestItemWidgetClass) return;
	UE_LOG(LogTemp, Log, TEXT("Call Refresh QuestList"));

	VerticalBox_QuestList->ClearChildren();

	auto QuestSubsystem = GetGameInstance()->GetSubsystem<UUPrototypeQuestSubsystem>();
	if(!QuestSubsystem) return;

	const TMap<FName, FQuestState>& QuestStates = QuestSubsystem->GetAllQuestStates();

	for(const auto& Pair : QuestStates)
	{
		const FName QuestID = Pair.Key;
		const FQuestState& State = Pair.Value;
		const FQuestData* Data = QuestSubsystem->GetQuestData(QuestID);
		if(!Data) continue;

		UQuestItemWidget* QuestWidget = CreateWidget<UQuestItemWidget>(this, QuestItemWidgetClass);
		if(QuestWidget)
		{
			UE_LOG(LogTemp, Log, TEXT("QuestWidget->VerticalBox_QuestList Bind!"));
			QuestWidget->SetQuestInfo(Data->QuestTitle, Data->QuestDescription, State.bIsCompleted);
			VerticalBox_QuestList->AddChildToVerticalBox(QuestWidget);
		}
	}
}

void UQuestUIWidget::QuestListUpdated(FName UpdatedQuestID)
{
	UE_LOG(LogTemp, Log, TEXT("Call QuestList Updated!"));
	RefreshQuestList();
}
