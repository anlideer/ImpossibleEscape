// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "IMScoreComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnScoreChanged, int, NewScore);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class IMPOSSIBLEESCAPE_API UIMScoreComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UIMScoreComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	void AddScore(int Amount);

	UFUNCTION(BlueprintCallable)
	int GetScore();

	UPROPERTY(BlueprintAssignable)
	FOnScoreChanged OnScoreChanged;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	int Score;

};
