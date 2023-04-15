// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "IMHealthComponent.h"
#include "IMBaseEnemy.generated.h"

class UIMHealthComponent;
UCLASS()
class IMPOSSIBLEESCAPE_API AIMBaseEnemy : public ACharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIMBaseEnemy();

protected:

	UPROPERTY(EditAnywhere, Category = "Basis")
	float MoveSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "Basis")
	TObjectPtr<UIMHealthComponent> HealthComp;


	UPROPERTY(EditAnywhere, Category = "Attack")
	TSubclassOf<AActor> ProjectileClass;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FTimerHandle TimerHandle;

	void Shoot();
	void ScheduleShoot();
};
