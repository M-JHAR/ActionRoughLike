// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotionPowerUp.h"
#include "SAttributeComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "SPlayerState.h"

ASHealthPotionPowerUp::ASHealthPotionPowerUp()
{
	HealAmount = 20.0f;

	CreditCost = 50;
}


void ASHealthPotionPowerUp::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn)) return;

	USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(InstigatorPawn);



	if (ensure(AttributeComp) && !AttributeComp->IsMaxHealth())
	{
		if (ASPlayerState* PS = InstigatorPawn->GetPlayerState<ASPlayerState>())
		{

			if (PS->RemoveCredits(CreditCost) && AttributeComp->ApplyHealthChange(this, HealAmount))
			{
				HideAndCooldownPowerUp();
			}
		}


	}

}


