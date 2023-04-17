// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IMBasePawn.h"
#include "IMSpecialEnemy.generated.h"

UCLASS()
class IMPOSSIBLEESCAPE_API AIMSpecialEnemy : public AIMBasePawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AIMSpecialEnemy();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Score")
	int EnemyPoints;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MinY;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MoveSpeed;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	FTimer TimeHandle;

	void Die() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
