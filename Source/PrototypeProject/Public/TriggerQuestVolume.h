// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TriggerQuestVolume.generated.h"

class UBoxComponent;
class UUserWidget;

UCLASS()
class PROTOTYPEPROJECT_API ATriggerQuestVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATriggerQuestVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public :
	UPROPERTY(EditAnywhere, Category = "Quest")
	TArray<FName> QuestIDs
	{
		"EnteredArea01",
		"EnteredArea02",
	};
private :
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComponent;
};
