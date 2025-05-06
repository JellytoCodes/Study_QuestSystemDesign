// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameSaveLoad.generated.h"

//½½·Ô °ü¸® USTRUCT
USTRUCT()
struct FSlotInfo
{
	GENERATED_BODY()

	UPROPERTY()
	bool bSaved = false;

	UPROPERTY()
	FString SlotName;
};

class UButton;
class UTextBlock;

UCLASS()
class PROTOTYPEPROJECT_API UGameSaveLoad : public UUserWidget
{
	GENERATED_BODY()

public :
	virtual void NativeConstruct() override;
	//Ã¹¹øÂ° ½½·Ô
	UPROPERTY(meta = (BindWidget))
	UButton* SlotButton_1;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SlotText_1;
	UPROPERTY(meta = (BindWidget))
	UButton* DeleteButton_1;

	//µÎ¹øÂ° ½½·Ô
	UPROPERTY(meta = (BindWidget))
	UButton* SlotButton_2;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* SlotText_2;
	UPROPERTY(meta = (BindWidget))
	UButton* DeleteButton_2;

protected :

	//1¹øÂ° ½½·Ô Save/Load/Delete
	UFUNCTION()
	void OnClickSlot1();
	UFUNCTION()
	void OnClickDelete1();

	//2¹øÂ° ½½·Ô Save/Load/Delete
	UFUNCTION()
	void OnClickSlot2();
	UFUNCTION()
	void OnClickDelete2();

	//½½·Ô Save / Load °ü¸®
	void SaveToSlot(int32 SlotIndex);
	void LoadFromSlot(int32 SlotIndex);
	void DeleteSlot(int32 SlotIndex);
};
