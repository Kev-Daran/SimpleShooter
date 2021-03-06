// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "EndGamePlayerController.generated.h"


/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AEndGamePlayerController : public APlayerController
{
	GENERATED_BODY()

	public:
	virtual void GameHasEnded(class AActor* EndGameFocus, bool bIsWinner) override;

	protected:

	virtual void BeginPlay() override;

	private:

	UPROPERTY(EditAnywhere)
	float RestartDelay = 5.f;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LoseScreenClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> WinScreenClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HUDClass;

	UPROPERTY(EditAnywhere)
	UUserWidget* HUD;

	FTimerHandle TimerHandle;
};
