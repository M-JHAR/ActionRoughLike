// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTTask_HealBack.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "AI/SAICharacter.h"
#include "SAttributeComponent.h"


EBTNodeResult::Type USBTTask_HealBack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);


	UBlackboardComponent* BBC = OwnerComp.GetBlackboardComponent();
	if (ensure(BBC))
	{
		AAIController* MyController = OwnerComp.GetAIOwner();
		if (ensure(MyController))
		{
			ASAICharacter* AICharacter = Cast<ASAICharacter>(MyController->GetPawn());

			if (ensure(AICharacter))
			{
				USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(AICharacter->GetComponentByClass(USAttributeComponent::StaticClass()));

				if (ensure(AttributeComp))
				{
					AttributeComp->ApplyHealthChange(AttributeComp->GetMaxHealh());
					return EBTNodeResult::Type::Succeeded;
				}
			}
		}
	}

	return EBTNodeResult::Type::Failed;
}
