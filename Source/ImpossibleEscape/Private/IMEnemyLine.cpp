// Fill out your copyright notice in the Description page of Project Settings.

#include "IMEnemyLine.h"
#include "IMBaseEnemy.h"
#include "Kismet/GameplayStatics.h"

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
	RealMaxY = MaxY - EnemyPerLine * IntervalVec.Y;
	RealMoveSpeed = InitialMoveSpeed;
	MoveDirection = 1.f;
	isMoving = true;

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
				}
			}
		}
	}
}

// Called every frame
void AIMEnemyLine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isMoving)
		DoMove();
}

void AIMEnemyLine::OnEnemyDied()
{
	CurrentEnemyCount--;
	float factor = (float)EnemyLineCount * (float)EnemyPerLine / (float)CurrentEnemyCount;
	if (factor > 3) 
		factor = 3;
	RealMoveSpeed = InitialMoveSpeed * factor;
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
		// TODO: more check to see if game end
		if (pos.X <= FinalX)
		{
			isMoving = false;
			if (GEngine)
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Lose"));

		}
		else
		{
			SetActorLocation(pos);
			MoveDirection = -MoveDirection;
		}
	}
}