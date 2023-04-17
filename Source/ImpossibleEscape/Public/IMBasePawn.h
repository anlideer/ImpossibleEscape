// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/SphereComponent.h"
#include "IMBasePawn.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLifeChanged, int, NewLifeCount);

UCLASS()
class IMPOSSIBLEESCAPE_API AIMBasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AIMBasePawn();

protected:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* MeshComp;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComp;

	UPROPERTY(EditDefaultsOnly, Category = "Basis")
	int LifeCount;	// how many lives left for this person

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(BlueprintAssignable)
	FOnLifeChanged OnLifeChanged;

	void TakeDamage();
	void Shoot();
	virtual void Die();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	FDateTime lastShootTime;

};
