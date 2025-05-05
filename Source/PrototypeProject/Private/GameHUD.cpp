// Fill out your copyright notice in the Description page of Project Settings.


#include "GameHUD.h"
#include "QuestUIWidget.h"
#include "UPrototypeQuestSubsystem.h"
#include "TimeManagerWidget.h"
#include "TimeManager.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "PrototypeProject/PrototypeProjectCharacter.h"

AGameHUD::AGameHUD()
{
    PrimaryActorTick.bCanEverTick = true;
    
    static ConstructorHelpers::FClassFinder<UQuestUIWidget> WidgetBPClass(TEXT("/Game/Blueprints/WBP_QuestUIWidget.WBP_QuestUIWidget_C"));
    if (WidgetBPClass.Succeeded())
    {
         QuestWidgetUI = WidgetBPClass.Class;
    }

    static ConstructorHelpers::FClassFinder<UTimeManagerWidget> TimerBPClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Blueprints/WBP_TimerUI.WBP_TimerUI_C'"));
    if (TimerBPClass.Succeeded())
    {
         TimerWidgetUI = TimerBPClass.Class;
    }
}

void AGameHUD::BeginPlay()
{
    Super::BeginPlay();

    Timer = GetGameInstance()->GetSubsystem<UTimeManager>();

    if(Timer != nullptr)
    {
        Timer->StartDefensePhase();
		UE_LOG(LogTemp, Warning, TEXT("Timer Start!"));
		Timer->OnDefenseTimeCompleted.AddDynamic(this, &AGameHUD::GameClear);
    }

    QuestWidget = CreateWidget<UQuestUIWidget>(GetWorld(), QuestWidgetUI);
    TimerWidget = CreateWidget<UTimeManagerWidget>(GetWorld(), TimerWidgetUI);

    TimerWidget->AddToViewport();
    QuestWidget->AddToViewport();
}

void AGameHUD::Tick(float DeltaSeconds)
{
    if (TimerWidget && Timer)
    {
        float Remaining = Timer->GetRemainingDefenseTime();
        int32 getsecond = FMath::FloorToInt(Remaining);
        int32 min = getsecond / 60;
        int32 sec = getsecond % 60;
        FString Formatted = FString::Printf(TEXT("%02d : %02d"), min, sec);
        TimerWidget->UpdateTimerText(Formatted);
    }
}

void AGameHUD::CompletedWidget(FName QuestID)
{
    Timer->PauseDefensePhase();
}

void AGameHUD::StartedWidget(FName QuestID)
{

}

void AGameHUD::GameClear()
{
    UE_LOG(LogTemp, Warning, TEXT("Mission Failed"));
    FTimerHandle ViewTimer;
    
    QuestWidget->TextSet();
    
    GetWorld()->GetTimerManager().SetTimer(ViewTimer, [&]()
    {
        QuestWidget->AddToViewport();
    }, 1.f, false);
}
