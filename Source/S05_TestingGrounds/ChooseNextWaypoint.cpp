// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrollingGuard.h" // TODO remove coupling
#include "PatrolRoute.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UE_LOG(LogTemp, Warning, TEXT("ExecuteTask début"));

	/*
	 * Get patrol points
	 */

	APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	UPatrolRoute* PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();

	if (!ensure(PatrolRoute)) { return EBTNodeResult::Failed; }

	TArray<AActor*> PatrolPoints = PatrolRoute->GetPatrolPoints();

	if (0 == PatrolPoints.Num()) 
	{
		UE_LOG(LogTemp, Warning, TEXT("A guard is missing patrolp oints"));
		return EBTNodeResult::Failed;
	}

	/*
	 * Set next waypoint
	 */
	// Get blackboard comp, PatrolData
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();

	// Get value for key IndexKey
	int32 Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);

	UE_LOG(LogTemp, Warning, TEXT("Index : %i"), Index);

	// Set the next Waypoint to go as "PatrolPoints[Index]"
	BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);

	/*
	 * Set next waypoint index to go after the next waypoint
	 */
	int32 NextIndex = (Index + 1) % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);


	UE_LOG(LogTemp, Warning, TEXT("NextIndex : %i"), NextIndex);

	UE_LOG(LogTemp, Warning, TEXT("ExecuteTask fin"));


	return EBTNodeResult::Succeeded;
}


