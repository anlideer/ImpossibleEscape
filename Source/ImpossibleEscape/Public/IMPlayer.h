// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IMBasePawn.h"
#include "IMScoreComponent.h"
#include "IMPlayer.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameEnd, bool, IsWin);

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Basis")
	TObjectPtr<UIMScoreComponent> ScoreComp;

	void MoveRight(float value);	// movement
	void ContinueGame();	// continue next level or restart
	void ExitGame();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(BlueprintReadOnly)
	bool Winned;
	UPROPERTY(BlueprintReadOnly)
	bool GameEnded;

	void Die() override;
	void SetGameEnd(bool IsWin);

	UPROPERTY(BlueprintAssignable)
	FOnGameEnd OnGameEnd;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	FString SlotName;

	void HandleSaveScore();
};
