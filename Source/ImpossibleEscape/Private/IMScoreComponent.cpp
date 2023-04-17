// Fill out your copyright notice in the Description page of Project Settings.


#include "IMScoreComponent.h"
#include "IMSaveGame.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UIMScoreComponent::UIMScoreComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

}


// Called when the game starts
void UIMScoreComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (UIMSaveGame* SaveGameInstance = Cast<UIMSaveGame>(UGameplayStatics::LoadGameFromSlot("IMSave", 0)))
	{
		Score = SaveGameInstance->CurrentScore;
	}
	else
	{
		Score = 0;
	}
}


// Called every frame
void UIMScoreComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UIMScoreComponent::AddScore(int Amount)
{
	Score += Amount;
	OnScoreChanged.Broadcast(Score);

}

int UIMScoreComponent::GetScore()
{
	return Score;
}

int UIMScoreComponent::GetHighestScore()
{
	if (UIMSaveGame* SaveGameInstance = Cast<UIMSaveGame>(UGameplayStatics::LoadGameFromSlot("IMSave", 0)))
	{
		return SaveGameInstance->HighestScore;
	}
	else
	{
		return Score;
	}
}