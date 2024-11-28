// Fill out your copyright notice in the Description page of Project Settings.


#include "SHealthPotionPowerUp.h"
#include "SAttributeComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

ASHealthPotionPowerUp::ASHealthPotionPowerUp()
{
	HealAmount = 20.0f;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");

	// we use sphere collision to handle interactive queries
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(RootComponent);
}


void ASHealthPotionPowerUp::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn)) return;

	USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(InstigatorPawn->GetComponentByClass(USAttributeComponent::StaticClass()));

	if (ensure(AttributeComp) && !AttributeComp->IsMaxHealth())
	{

		if (AttributeComp->ApplyHealthChange(this, HealAmount))
		{
			HideAndCooldownPowerUp();
		}
	}

}


