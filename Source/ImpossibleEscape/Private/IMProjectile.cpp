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
	StaticMesh->SetEnableGravity(false);
	RootComponent = StaticMesh;

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComp");
	MovementComp->InitialSpeed = 500.f;
	MovementComp->MaxSpeed = 500.f;
	MovementComp->bRotationFollowsVelocity = true;
	MovementComp->bInitialVelocityInLocalSpace = true;
	MovementComp->ProjectileGravityScale = 0.f;

	StaticMesh->IgnoreActorWhenMoving(GetInstigator(), true);
}

// Called when the game starts or when spawned
void AIMProjectile::BeginPlay()
{
	Super::BeginPlay();

	StaticMesh->OnComponentHit.AddDynamic(this, &AIMProjectile::OnActorHit);
}

// Called every frame
void AIMProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AIMProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	TryDestructWall(OtherActor, Hit);	// bp implemented


	if (AIMProjectile* OtherProjectile = Cast<AIMProjectile>(OtherActor))
	{
		OtherProjectile->Destroy();
	}
	this->Destroy();
}