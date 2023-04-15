// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "IMHealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class IMPOSSIBLEESCAPE_API UIMHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UIMHealthComponent();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Basis")
	int LifeCount;	// how many lives left for this person

	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	bool TakeDamage(); // return true if still alive after that, return false if dead

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
