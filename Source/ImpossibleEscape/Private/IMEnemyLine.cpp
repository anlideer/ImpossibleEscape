// Fill out your copyright notice in the Description page of Project Settings.


#include "IMEnemyLine.h"

// Sets default values
AIMEnemyLine::AIMEnemyLine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AIMEnemyLine::BeginPlay()
{
	Super::BeginPlay();
	
	// generate a line of the same type of enemies
	if (ensure(EnemyClass))
	{
		for (int i = 0; i < EnemyCount; i++)
		{
			FRotator SpawnRotator = FVector(0, 1, 0).Rotation();
			FVector StartLocation = GetActorLocation() + i * IntervalVec;
			FTransform SpawnTransform = FTransform(SpawnRotator, StartLocation);
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			SpawnParams.Instigator = this;
			GetWorld()->SpawnActor<AActor>(EnemyClass, SpawnTransform, SpawnParams);
		}
	}
}

// Called every frame
void AIMEnemyLine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

