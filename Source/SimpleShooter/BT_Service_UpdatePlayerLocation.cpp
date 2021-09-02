// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Service_UpdatePlayerLocation.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBT_Service_UpdatePlayerLocation::UBT_Service_UpdatePlayerLocation()
{
    NodeName = "UpdateLocationIfSeen";
}

void UBT_Service_UpdatePlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if(PlayerPawn == nullptr)
    {
        return;
    }

    AAIController* AIController = OwnerComp.GetAIOwner();
    
    if(AIController == nullptr)
    {
        return;
    }
    
    if(AIController->LineOfSightTo(PlayerPawn))
    {
        OwnerComp.GetBlackboardComponent()->SetValueAsObject(TEXT("Player"), PlayerPawn);
    }
    else
    {
        OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("Player"));
    }
}

