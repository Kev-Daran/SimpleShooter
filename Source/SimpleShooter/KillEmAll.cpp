// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAll.h"
#include "EndGamePlayerController.h"
#include "GameFramework/Controller.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterAI.h"

void AKillEmAll::PawnKilled(APawn* PawnKilled)
{
    Super::PawnKilled(PawnKilled);
    UE_LOG(LogTemp, Warning, TEXT("Da Pawn was killeded"));

    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    
    if(PlayerController != nullptr)
    {
        EndGame(false);
    }

    for(AShooterAI* ShooterAI : TActorRange<AShooterAI>(GetWorld()))
    {
        if(!ShooterAI->IsDead())
        {
            return;
        }
    }
    EndGame(true);

}

void AKillEmAll::EndGame(bool bIsPlayerWinner)
{
    for(AController* Controller : TActorRange<AController>(GetWorld()))
    {
        bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
        Controller->GameHasEnded(nullptr, bIsWinner);
    }
}