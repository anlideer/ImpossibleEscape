// Fill out your copyright notice in the Description page of Project Settings.


#include "IMBaseEnemy.h"

// Sets default values
AIMBaseEnemy::AIMBaseEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AIMBaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AIMBaseEnemy::ScheduleShoot, FMath::RandRange(0.2f, 2.f), false);
}

// Called every frame
void AIMBaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AIMBaseEnemy::ScheduleShoot()
{
	Shoot();
	//TimerHandle.Invalidate();
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AIMBaseEnemy::ScheduleShoot, FMath::RandRange(1.f, 5.f), false);
}


void AIMBaseEnemy::Shoot()
{
	if (ensure(ProjectileClass))
	{
		FRotator SpawnRotator = FVector(-1, 0, 0).Rotation();
		FVector StartLocation = GetActorLocation();	// fake, should be shot from the hand
		FTransform SpawnTransform = FTransform(SpawnRotator, StartLocation);
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;
		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTransform, SpawnParams);
	}
}