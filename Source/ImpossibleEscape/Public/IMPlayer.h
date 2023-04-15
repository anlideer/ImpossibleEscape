// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "IMPlayer.generated.h"

UCLASS()
class IMPOSSIBLEESCAPE_API AIMPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AIMPlayer();

protected:

	UPROPERTY(EditAnywhere, Category="Basis")
	AActor* GlobalCameraRef;	// a global top-down camera to be used

	UPROPERTY(EditAnywhere, Category="Basis")
	float MoveSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Basis")
	int LifeCount;	// how many lives left for this person

	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;

	void MoveRight(float value);	// movement
	void Shoot();	// player shoots
	bool TakeDamage(); // return true if still alive after that, return false if dead

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
