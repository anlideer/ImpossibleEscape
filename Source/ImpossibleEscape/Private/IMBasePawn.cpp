// Fill out your copyright notice in the Description page of Project Settings.


#include "IMBasePawn.h"

// Sets default values
AIMBasePawn::AIMBasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	RootComponent = SphereComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetupAttachment(SphereComp);
}

// Called when the game starts or when spawned
void AIMBasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIMBasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AIMBasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AIMBasePawn::Shoot()
{
	if (ensure(ProjectileClass))
	{
		FTransform SpawnTransform = FTransform(GetActorRotation(), GetActorLocation());
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;
		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTransform, SpawnParams);
	}
}

void AIMBasePawn::TakeDamage()
{
	LifeCount--;
	OnLifeChanged.Broadcast(LifeCount);
	if (LifeCount <= 0)
	{
		Die();
	}
}

// parent class empty implemention will not be called
void AIMBasePawn::Die() {}

