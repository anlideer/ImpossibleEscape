// Fill out your copyright notice in the Description page of Project Settings.


#include "IMPlayer.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AIMPlayer::AIMPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MoveSpeed = 100.f;
}

// Called when the game starts or when spawned
void AIMPlayer::BeginPlay()
{
	Super::BeginPlay();
	
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
}

void AIMPlayer::MoveRight(float value)
{
	FVector pos = GetActorLocation();
	pos.Y += value * MoveSpeed * UGameplayStatics::GetWorldDeltaSeconds(this);
	SetActorLocation(pos);
}

void AIMPlayer::Shoot()
{
	FRotator SpawnRotator = FVector(1, 0, 0).Rotation();
	FVector StartLocation = GetActorLocation();	// fake, should be shot from the hand
	FTransform SpawnTransform = FTransform(SpawnRotator, StartLocation);
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Instigator = this;
	GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTransform, SpawnParams);
}