// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTService_CheckLowHealth.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "AI/SAICharacter.h"
#include "SAttributeComponent.h"


USBTService_CheckLowHealth::USBTService_CheckLowHealth()
{
	LowHealthFraction = 0.4f;
}

void USBTService_CheckLowHealth::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);


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
					bool bIsLowHealth = (AttributeComp->GetHealh() / AttributeComp->GetMaxHealh()) < LowHealthFraction;
					BBC->SetValueAsBool(LowHealthKey.SelectedKeyName, bIsLowHealth);
				}	
			}
		}
	}


}
