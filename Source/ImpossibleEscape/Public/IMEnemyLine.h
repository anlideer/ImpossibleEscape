// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "IMEnemyLine.generated.h"

// manager of enemies
UCLASS()
class IMPOSSIBLEESCAPE_API AIMEnemyLine : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIMEnemyLine();

protected:

	UPROPERTY(EditAnywhere, Category = "Generation")
	int EnemyPerLine;

	UPROPERTY(EditAnywhere, Category = "Generation")
	int EnemyLineCount;

	UPROPERTY(EditAnywhere, Category = "Generation")
	FVector IntervalVec;

	UPROPERTY(EditAnywhere, Category = "Generation")
	FVector SpecialEnemyStartPoint;

	UPROPERTY(EditAnywhere, Category = "EnemyPreset")
	TSubclassOf<AActor> EnemyClass;

	UPROPERTY(EditAnywhere, Category = "EnemyPreset")
	TSubclassOf<AActor> SecondEnemyClass;

	UPROPERTY(EditAnywhere, Category = "EnemyPreset")
	TSubclassOf<AActor> ThirdEnemyClass;

	UPROPERTY(EditAnywhere, Category = "EnemyPreset")
	TSubclassOf<AActor> SpecialEnemyClass;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MinY;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MaxY;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float FinalX;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float InitialMoveSpeed;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	void OnEnemyDied(int X, int Y);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	int CurrentEnemyCount;
	float RealMinY;
	float RealMaxY;	// considering enemy count per line
	float RealMoveSpeed;	// dynamica based on enemy alive
	float MoveDirection;
	bool isMoving;
	TArray<TArray<AActor*>> EnemyList;

	FTimerHandle TimerHandle;

	void GenerateEnemyBlock();
	void DoMove();
	void ReCalculateBorder();
	void GenerateSpecialEnemy();
};
