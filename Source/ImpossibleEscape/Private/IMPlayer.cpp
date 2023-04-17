// Fill out your copyright notice in the Description page of Project Settings.


#include "IMPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "IMPlayerController.h"
#include "IMSaveGame.h"
#include "IMScoreComponent.h"

// Sets default values
AIMPlayer::AIMPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MoveSpeed = 100.f;
	ScoreComp = CreateDefaultSubobject<UIMScoreComponent>("ScoreComp");

	SlotName = "IMSave";
}

// Called when the game starts or when spawned
void AIMPlayer::BeginPlay()
{
	Super::BeginPlay();
	
	Winned = false;
	GameEnded = false;
	APlayerController* MyPlayerController = GetWorld()->GetFirstPlayerController();
	MyPlayerController->SetViewTargetWithBlend(GlobalCameraRef);
}

// Called every frame
void AIMPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AIMPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveRight", this, &AIMPlayer::MoveRight);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AIMPlayer::Shoot);
	PlayerInputComponent->BindAction("ContinueGame", IE_Pressed, this, &AIMPlayer::ContinueGame);
	PlayerInputComponent->BindAction("ExitGame", IE_Pressed, this, &AIMPlayer::ExitGame);
}

void AIMPlayer::MoveRight(float value)
{
	if (!GameEnded)
	{
		FVector pos = GetActorLocation();
		pos.Y += value * MoveSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
		if (pos.Y <= MaxY && pos.Y >= MinY)
			SetActorLocation(pos);
	}
}

void AIMPlayer::Die()
{
	MeshComp->SetVisibility(false);
	SetGameEnd(false);
}

void AIMPlayer::SetGameEnd(bool IsWin)
{
	Winned = IsWin;
	GameEnded = true;

	HandleSaveScore();
	OnGameEnd.Broadcast(IsWin);
}

void AIMPlayer::HandleSaveScore() 
{
	int MyScore = 0;
	if (UIMScoreComponent* MyScoreComp =
		Cast<UIMScoreComponent>(
			UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetComponentByClass(UIMScoreComponent::StaticClass())))
	{
		MyScore = MyScoreComp->GetScore();
	}

	// store
	UIMSaveGame* SaveGameInstance;
	if (UIMSaveGame* TmpInstance = Cast<UIMSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0)))
	{
		SaveGameInstance = TmpInstance;
		int highestScore = SaveGameInstance->HighestScore;
		if (MyScore > highestScore)
		{
			SaveGameInstance->HighestScore = MyScore;
		}
	}
	else
	{
		SaveGameInstance = Cast<UIMSaveGame>(UGameplayStatics::CreateSaveGameObject(UIMSaveGame::StaticClass()));
		SaveGameInstance->HighestScore = MyScore;
		SaveGameInstance->Level = 0;
	}

	if (Winned)
	{
		SaveGameInstance->CurrentScore = MyScore;
		SaveGameInstance->Level++;
	}
	else
	{
		SaveGameInstance->CurrentScore = 0;
		SaveGameInstance->Level = 0;
	}

	bool res = UGameplayStatics::SaveGameToSlot(SaveGameInstance, SlotName, 0);
}

// normally these should not go to player class, but I'm in a hurry...
void AIMPlayer::ContinueGame()
{
	if (!GameEnded)
		return;

	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void AIMPlayer::ExitGame()
{
	if (!GameEnded)
		return;

	if (UIMSaveGame* SaveGameInstance = Cast<UIMSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, 0)))
	{
		SaveGameInstance->CurrentScore = 0;
		SaveGameInstance->Level = 0;
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, SlotName, 0);
	}

	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Type::Quit, false);
}