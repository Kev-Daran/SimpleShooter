// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAI.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"

void AShooterAI::BeginPlay()
{
    Super::BeginPlay();
    if(EnemyAI != nullptr)
    {
        RunBehaviorTree(EnemyAI);

        GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());

        // GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation());
    }
}


void AShooterAI::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    // APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);    


    // if(AAIController::LineOfSightTo(PlayerPawn))
    // {
    //     GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation());
    //     GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation());
    // }
    // else
    // {
    //     GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));
    // }

    // else
    // {
    //     AAIController::ClearFocus(EAIFocusPriority::Gameplay);
    //     AAIController::StopMovement();
    // }
}

bool AShooterAI::IsDead() const
{
    AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(GetPawn());

    if(ControlledCharacter != nullptr)
    {
        return ControlledCharacter->IsDead();
    }

    return true;
}