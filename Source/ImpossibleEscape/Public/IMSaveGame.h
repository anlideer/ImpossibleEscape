// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "IMSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class IMPOSSIBLEESCAPE_API UIMSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = "Basic")
	int HighestScore;	// save highest score

	UPROPERTY(EditAnywhere, Category = "Basic")
	int CurrentScore;	// save score before proceeding to the next level

	UPROPERTY(EditAnywhere, Category = "Basic")
	int Level;
};
