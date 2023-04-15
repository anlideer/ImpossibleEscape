// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "IMEnemyLine.generated.h"

UCLASS()
class IMPOSSIBLEESCAPE_API AIMEnemyLine : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIMEnemyLine();

protected:

	UPROPERTY(EditAnywhere, Category = "Generation")
	int EnemyCount;

	UPROPERTY(EditAnywhere, Category = "Generation")
	FVector IntervalVec;

	UPROPERTY(EditAnywhere, Category = "Generation")
	TSubclassOf<AActor> EnemyClass;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
