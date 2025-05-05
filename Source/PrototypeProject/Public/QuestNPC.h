// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UPrototypeQuestSubsystem.h"
#include "QuestNameDefs.h"
#include "QuestNPC.generated.h"

UCLASS()
class PROTOTYPEPROJECT_API AQuestNPC : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, Category = "Collision", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* CollisionComp;

public:	
	// Sets default values for this actor's properties
	AQuestNPC();

	UPROPERTY(EditAnywhere, Category = "Quest")
	EQuestName QuestID;

	UPROPERTY(EditDefaultsOnly, Category = "Quest")
	EQuestTriggerType TriggerType = EQuestTriggerType::Interaction;

	UPROPERTY(EditDefaultsOnly, Category = "Quest")
	EQuestConditionType ConditionType = EQuestConditionType::PickupItem;

	bool Interact(class APrototypeProjectCharacter* PlayerCharacter);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
