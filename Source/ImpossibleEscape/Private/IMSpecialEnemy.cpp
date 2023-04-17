// Fill out your copyright notice in the Description page of Project Settings.


#include "IMSpecialEnemy.h"
#include "IMScoreComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AIMSpecialEnemy::AIMSpecialEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EnemyPoints = 200;
}

// Called when the game starts or when spawned
void AIMSpecialEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIMSpecialEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector pos = GetActorLocation();
	pos.Y += -MoveSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
	if (pos.Y >= MinY)
	{
		SetActorLocation(pos);
	}
	else
	{
		this->Destroy();
	}

}

// Called to bind functionality to input
void AIMSpecialEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AIMSpecialEnemy::Die()
{
	if (UIMScoreComponent* ScoreComp =
		Cast<UIMScoreComponent>(
			UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetComponentByClass(UIMScoreComponent::StaticClass())))
	{
		ScoreComp->AddScore(EnemyPoints);
	}

	this->Destroy();
}