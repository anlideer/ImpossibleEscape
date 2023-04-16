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
	
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AIMBaseEnemy::ScheduleShoot, FMath::RandRange(0.2f, 5.f), false);
}

// Called every frame
void AIMBaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AIMBaseEnemy::ScheduleShoot()
{
	// detect if there is an enemy in front of this
	FHitResult Hit;
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);
	FVector StartPoint = GetActorLocation() + FVector(-50, 0, 0);	// skip its own collision
	FVector EndPoint = GetActorLocation() + FVector(-200, 0, 0);

	GetWorld()->LineTraceSingleByObjectType(Hit, StartPoint, EndPoint, ObjectQueryParams);
	//DrawDebugLine(GetWorld(), StartPoint, EndPoint, FColor::Blue, false, 2.f, 0U, 1.f);
	AActor* HitActor = Hit.GetActor();
	if (HitActor == nullptr)
	{
		Shoot();
	}

	GetWorldTimerManager().SetTimer(TimerHandle, this, &AIMBaseEnemy::ScheduleShoot, FMath::RandRange(2.f, 5.f), false);
}

void AIMBaseEnemy::Die()
{
	Manager->OnEnemyDied();
	this->Destroy();
}