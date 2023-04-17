// Fill out your copyright notice in the Description page of Project Settings.

#include "IMEnemyLine.h"
#include "IMBaseEnemy.h"
#include "IMPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "IMSaveGame.h"

// Sets default values
AIMEnemyLine::AIMEnemyLine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InitialMoveSpeed = 70.f;
}

// Called when the game starts or when spawned
void AIMEnemyLine::BeginPlay()
{
	Super::BeginPlay();

	CurrentEnemyCount = EnemyLineCount * EnemyPerLine;
	RealMinY = MinY;
	RealMaxY = MaxY - (EnemyPerLine - 1) * IntervalVec.Y;
	RealMoveSpeed = InitialMoveSpeed;
	MoveDirection = 1.f;
	isMoving = true;

	// get level
	int level = 0;
	if (UIMSaveGame* SaveGameInstance = Cast<UIMSaveGame>(UGameplayStatics::LoadGameFromSlot("IMSave", 0)))
	{
		level = SaveGameInstance->Level;
	}
	if (level > 0)
	{
		FVector pos = GetActorLocation();
		pos.X -= level * IntervalVec.X;
		SetActorLocation(pos);
	}


	GenerateEnemyBlock();
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AIMEnemyLine::GenerateSpecialEnemy, FMath::RandRange(3.f, 6.f), false);
}

// Called every frame
void AIMEnemyLine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AIMPlayer* GlobalPlayer = Cast<AIMPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
	{
		if (GlobalPlayer->GameEnded)
			isMoving = false;
	}

	if (isMoving)
	{
		DoMove();
	}
}

void AIMEnemyLine::OnEnemyDied(int X, int Y)
{
	CurrentEnemyCount--;

	if (CurrentEnemyCount <= 0)
	{
		isMoving = false;
		if (AIMPlayer* GlobalPlayer = Cast<AIMPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
		{
			GlobalPlayer->SetGameEnd(true);
		}
	}

	// recalculate speed
	float factor = (float)EnemyLineCount * (float)EnemyPerLine / (float)CurrentEnemyCount;
	if (factor > 3) 
		factor = 3;
	RealMoveSpeed = InitialMoveSpeed * factor;

	// recalculate miny maxy (moving area)
	EnemyList[X][Y] = nullptr;
	ReCalculateBorder();
}

void AIMEnemyLine::GenerateEnemyBlock()
{
	// init enemy array
	EnemyList.SetNum(EnemyLineCount);
	for (int c = 0; c < EnemyLineCount; c++)
		EnemyList[c].SetNum(EnemyPerLine);

	// generate a line of the same type of enemies
	if (ensure(EnemyClass) && ensure(SecondEnemyClass) && ensure(ThirdEnemyClass))
	{
		for (int i = 0; i < EnemyLineCount; i++)
		{
			for (int j = 0; j < EnemyPerLine; j++)
			{
				FRotator SpawnRotator = FVector(-1, 0, 0).Rotation();
				FVector StartLocation = GetActorLocation() +
					i * FVector(IntervalVec.X, 0, 0) +
					j * FVector(0, IntervalVec.Y, 0);
				FTransform SpawnTransform = FTransform(SpawnRotator, StartLocation);
				FActorSpawnParameters SpawnParams;
				SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				SpawnParams.Instigator = this;

				AActor* SpawnedActor;
				if (i % 3 == 0)
					SpawnedActor = GetWorld()->SpawnActor<AActor>(EnemyClass, SpawnTransform, SpawnParams);
				else if (i % 3 == 1)
					SpawnedActor = GetWorld()->SpawnActor<AActor>(SecondEnemyClass, SpawnTransform, SpawnParams);
				else
					SpawnedActor = GetWorld()->SpawnActor<AActor>(ThirdEnemyClass, SpawnTransform, SpawnParams);

				SpawnedActor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
				if (AIMBaseEnemy* SpawnedEnemy = Cast<AIMBaseEnemy>(SpawnedActor))
				{
					SpawnedEnemy->Manager = this;
					SpawnedEnemy->IndexX = i;
					SpawnedEnemy->IndexY = j;
				}
				EnemyList[i][j] = SpawnedActor;
			}
		}
	}
}

void AIMEnemyLine::DoMove()
{
	FVector pos = GetActorLocation();
	pos.Y += MoveDirection * RealMoveSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
	if (pos.Y <= RealMaxY && pos.Y >= RealMinY)
	{
		SetActorLocation(pos);
	}
	else
	{
		pos = GetActorLocation();
		pos.X -= IntervalVec.X;
		if (pos.X < FinalX)
		{
			isMoving = false;
			if (AIMPlayer* GlobalPlayer = Cast<AIMPlayer>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0)))
			{
				GlobalPlayer->SetGameEnd(false);
			}
		}
		else
		{
			SetActorLocation(pos);
			MoveDirection = -MoveDirection;
		}
	}
}

void AIMEnemyLine::ReCalculateBorder()
{
	int StartY = 0;
	int EndY = EnemyPerLine - 1;
	for (int j = 0; j < EnemyPerLine; j++)
	{
		bool isEmpty = true;
		for (int i = 0; i < EnemyLineCount; i++)
		{
			if (EnemyList[i][j] != nullptr)
			{
				isEmpty = false;
				break;
			}
		}
		if (isEmpty)
			StartY++;
		else
			break;
	}
	for (int j = EnemyPerLine - 1; j >= 0; j--)
	{
		bool isEmpty = true;
		for (int i = EnemyLineCount - 1; i >= 0; i--)
		{
			if (EnemyList[i][j] != nullptr)
			{
				isEmpty = false;
				break;
			}
		}
		if (isEmpty)
			EndY--;
		else
			break;
	}

	RealMinY = MinY - StartY * IntervalVec.Y;
	RealMaxY = MaxY - EndY * IntervalVec.Y;
}

void AIMEnemyLine::GenerateSpecialEnemy()
{
	if (ensure(SpecialEnemyClass) && isMoving)
	{
		FTransform SpawnTransform = FTransform(FRotator(0, 180, 0), SpecialEnemyStartPoint);
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;
		GetWorld()->SpawnActor<AActor>(SpecialEnemyClass, SpawnTransform, SpawnParams);

		GetWorldTimerManager().SetTimer(TimerHandle, this, &AIMEnemyLine::GenerateSpecialEnemy, FMath::RandRange(15.f, 30.f), false);
	}
}