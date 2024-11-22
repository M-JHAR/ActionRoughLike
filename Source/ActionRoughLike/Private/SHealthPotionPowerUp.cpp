// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotionPowerUp.h"
#include "SAttributeComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

ASHealthPotionPowerUp::ASHealthPotionPowerUp()
{
	HealAmount = 20.0f;

	ReUseTime = 10.0f;

}


void ASHealthPotionPowerUp::Interact_Implementation(APawn* InstigatorPawn)
{
	if (ensure(InstigatorPawn))
	{
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(InstigatorPawn->GetComponentByClass(USAttributeComponent::StaticClass()));

		if (AttributeComp->GetHealh() < 100.0f)
		{
			AttributeComp->ApplyHealthChange(HealAmount);

			DeactiveActorComponents();
			GetWorldTimerManager().SetTimer(TimerHande_ItemUsed, this, &ASHealthPotionPowerUp::ReactiveItem_TimeElapsed, ReUseTime);
		}
	}
}

void ASHealthPotionPowerUp::DeactiveActorComponents()
{
	SphereComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetVisibility(false);
}


void ASHealthPotionPowerUp::ReactiveItem_TimeElapsed()
{
	ReactiveActorComponents();
}

void ASHealthPotionPowerUp::ReactiveActorComponents()
{
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshComp->SetVisibility(true);
}




