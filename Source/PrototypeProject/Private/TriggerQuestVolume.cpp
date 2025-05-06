// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerQuestVolume.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "QuestUIWidget.h"
#include "GameHUD.h"

// Sets default values
ATriggerQuestVolume::ATriggerQuestVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	RootComponent = BoxComponent;
	BoxComponent->SetCollisionProfileName(TEXT("Trigger"));
	BoxComponent->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void ATriggerQuestVolume::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ATriggerQuestVolume::OnOverlapBegin);
}

void ATriggerQuestVolume::OnOverlapBegin(UPrimitiveComponent *OverlappedComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{
	if(ACharacter* Character = Cast<ACharacter>(OtherActor))
	{
		//퀘스트 서브시스템 할당 및 로드 Failed 시 return
		auto QuestSystem = GetGameInstance()->GetSubsystem<UUPrototypeQuestSubsystem>();
		if(!QuestSystem || QuestID.IsNone()) return;

		//퀘스트 데이터테이블 할당 및 로드 Failed 시 return
		const FQuestData* QuestData = QuestSystem->GetQuestData(QuestID);
		if(!QuestData) return;

		//이미 완료된 퀘스트 Skip을 위한 장치
		if(QuestSystem->IsQuestCompleted(QuestID)) return;

		//퀘스트 Trigger 타입 검사
		if(QuestData->TriggerType != EQuestTriggerType::Trigger) return;

		//퀘스트 시작 처리
		if(!QuestSystem->IsQuestStarted(QuestID))
		{
			QuestSystem->SetQuestStarted(QuestID);
			UE_LOG(LogTemp, Log, TEXT("Started Quest :%s"), *QuestData->QuestTitle.ToString());
		}

		//퀘스트 완료 처리
		else if(QuestData->ConditionType == EQuestConditionType::ReachArea && 
		QuestSystem->IsQuestStarted(QuestID) && !QuestSystem->IsQuestCompleted(QuestID))
		{
			QuestSystem->SetQuestCompleted(QuestID);
			UE_LOG(LogTemp, Log, TEXT("Completed Quest :%s"), *QuestData->QuestTitle.ToString());
		}
	}

	//중복 감지 방지를 위해 제거
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Destroy();
}
