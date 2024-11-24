// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_CheckAttackRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

void USBTService_CheckAttackRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	// Check distance between ai and target actor

	UBlackboardComponent* BlackboradComp = OwnerComp.GetBlackboardComponent();
	if (ensure(BlackboradComp))
	{
		AActor* TargetActor = Cast<AActor>(BlackboradComp->GetValueAsObject("TargetActor"));
		if (TargetActor)
		{
			AAIController* MyController = OwnerComp.GetAIOwner();
			if (ensure(MyController))
			{
				APawn* AIPawn = MyController->GetPawn();
				if (ensure(AIPawn))
				{
					float DistanceTo = FVector::Distance(TargetActor->GetActorLocation(), AIPawn->GetActorLocation());

					bool bWithRange = DistanceTo < 2000.0f;

					bool bHasLOS = false;
					if (bWithRange)
					{
						bHasLOS = MyController->LineOfSightTo(TargetActor);
					}

																				// If False Follow Player
					BlackboradComp->SetValueAsBool(AttackRangeKey.SelectedKeyName, (bWithRange && bHasLOS));
				}
			}
		}
	}
}
