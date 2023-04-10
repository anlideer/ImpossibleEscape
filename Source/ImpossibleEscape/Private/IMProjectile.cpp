// Fill out your copyright notice in the Description page of Project Settings.


#include "IMProjectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AIMProjectile::AIMProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	RootComponent = StaticMesh;

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 500.f;
	MovementComp->MaxSpeed = 500.f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
}

// Called when the game starts or when spawned
void AIMProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AIMProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

