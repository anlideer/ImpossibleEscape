// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IMBasePawn.h"
#include "IMScoreComponent.h"
#include "IMPlayer.generated.h"

class UIMScoreComponent;

UCLASS()
class IMPOSSIBLEESCAPE_API AIMPlayer : public AIMBasePawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AIMPlayer();

protected:

	UPROPERTY(EditAnywhere, Category="Basis")
	AActor* GlobalCameraRef;	// a global top-down camera to be used

	UPROPERTY(EditAnywhere, Category="Movement")
	float MoveSpeed;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MinY;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MaxY;

	UPROPERTY(VisibleAnywhere, Category = "Basis")
	UIMScoreComponent* ScoreComp;

	void MoveRight(float value);	// movement
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	void Die() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
