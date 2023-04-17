// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "IMEnemyLine.h"
#include "IMBasePawn.h"
#include "IMBaseEnemy.generated.h"

UCLASS()
class IMPOSSIBLEESCAPE_API AIMBaseEnemy : public AIMBasePawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIMBaseEnemy();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Score")
	int EnemyPoints;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	AIMEnemyLine* Manager;
	int IndexX;
	int IndexY;

	void Die() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FTimerHandle TimerHandle;

	void ScheduleShoot();
};
