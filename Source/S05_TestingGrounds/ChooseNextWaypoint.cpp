// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get blackboard comp, PatrolData
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	// Get value for key IndexKey
	int32 Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);

	UE_LOG(LogTemp, Warning, TEXT("Waypoint index : %i"), Index);
	
	return EBTNodeResult::Succeeded;
}


