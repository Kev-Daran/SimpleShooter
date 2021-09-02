// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Service_BlackboardBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBT_Service_BlackboardBase::UBT_Service_BlackboardBase()
{
    NodeName = "Update Player Location";
}

void UBT_Service_BlackboardBase::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld() , 0);

    if(PlayerPawn == nullptr)
    {
        return;
    }


    OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), PlayerPawn->GetActorLocation());
}