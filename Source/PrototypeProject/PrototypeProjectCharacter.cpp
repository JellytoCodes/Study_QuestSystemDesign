// Copyright Epic Games, Inc. All Rights Reserved.

#include "PrototypeProjectCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "UPrototypeQuestSubsystem.h"
#include "TimeManager.h"
#include "QuestNPC.h"
#include "GameHUD.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// APrototypeProjectCharacter

APrototypeProjectCharacter::APrototypeProjectCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

void APrototypeProjectCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	Timer = GetGameInstance()->GetSubsystem<UTimeManager>();
}

void APrototypeProjectCharacter::Tick(float DeltaSecond)
{
	Super::Tick(DeltaSecond);

}

void APrototypeProjectCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) 
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APrototypeProjectCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APrototypeProjectCharacter::Look);
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &APrototypeProjectCharacter::Pause);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &APrototypeProjectCharacter::Interact);
		EnhancedInputComponent->BindAction(QuestTestAction, ETriggerEvent::Started, this, &APrototypeProjectCharacter::NotifyItemPicked);
		EnhancedInputComponent->BindAction(SaveLoadAction, ETriggerEvent::Started, this, &APrototypeProjectCharacter::SaveLoad);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void APrototypeProjectCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APrototypeProjectCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APrototypeProjectCharacter::Pause(const FInputActionValue &Value)
{
	if(!Timer->IsPaused())
	{
		Timer->PauseDefensePhase();
	}
	else if(Timer->IsPaused())
	{
		Timer->ResumeDefensePhase();
	}
}

void APrototypeProjectCharacter::Interact(const FInputActionValue &Value)
{
	FHitResult Hit;
	FVector Start = FollowCamera->GetComponentLocation();
	FVector End = Start +FollowCamera->GetForwardVector() * 700.f;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	if(GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, Params))
	{
		UE_LOG(LogTemp, Warning, TEXT("Interact!"));
		DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.0f, 0, 2.0f);

		UPrimitiveComponent* HitComp = Hit.GetComponent();
		if(HitComp)
		{
			UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *Hit.GetActor()->GetName());
			UE_LOG(LogTemp, Warning, TEXT("Hit Comp: %s"), *HitComp->GetName());

			if(AQuestNPC* NPC = Cast<AQuestNPC>(HitComp->GetOwner()))
			{
				UE_LOG(LogTemp, Warning, TEXT("NPC Interact!"));
				NPC->Interact(this);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("No actor hit"));
			}
		}
	}
}

void APrototypeProjectCharacter::SaveLoad(const FInputActionValue &Value)
{
	if(APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if(AGameHUD* HUD = Cast<AGameHUD>(PlayerController->GetHUD()))
		{
			HUD->SaveLoadViewWidget();
		}
	}
}

void APrototypeProjectCharacter::NotifyItemPicked()
{
	if(UUPrototypeQuestSubsystem* QuestSys = GetGameInstance()->GetSubsystem<UUPrototypeQuestSubsystem>())
	{
		UE_LOG(LogTemp, Warning, TEXT("NotifyItemPicked!"));
		QuestSys->TryCompleteQuest("KEY001");
	}
}
