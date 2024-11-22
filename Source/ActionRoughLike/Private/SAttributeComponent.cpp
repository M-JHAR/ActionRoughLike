// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"


USAttributeComponent::USAttributeComponent()
{
	MaxHealth = 100.0f;
	Health = MaxHealth;
}

bool USAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

bool USAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;
	Health = FMath::Clamp(Health, 0.0f, MaxHealth);

	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);

	return true;
}

float USAttributeComponent::GetHealh() const
{
	return Health;
}
