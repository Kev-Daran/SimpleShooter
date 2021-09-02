// Fill out your copyright notice in the Description page of Project Settings.


#include "EndGamePlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"

void AEndGamePlayerController::BeginPlay()
{
    Super::BeginPlay();
    HUD = CreateWidget(this, HUDClass);
    if(HUD != nullptr)
    {
        HUD->AddToViewport();
    }
}

void AEndGamePlayerController::GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    // UE_LOG(LogTemp, Warning, TEXT("Da Game has ended!"));

    HUD->RemoveFromViewport();

    if(!bIsWinner)
    {
        UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);

        if(LoseScreen != nullptr)
        {
            LoseScreen->AddToViewport();
        }
    }

    else
    {
        UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);
        if(WinScreen != nullptr)
        {
            WinScreen->AddToViewport();
        }
    }


    GetWorldTimerManager().SetTimer(TimerHandle, this, &APlayerController::RestartLevel, RestartDelay);
}