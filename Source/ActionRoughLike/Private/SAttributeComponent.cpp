// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"


USAttributeComponent::USAttributeComponent()
{
	Health = 100.0f;
}

bool USAttributeComponent::ApplyHealthChange(float Delta)
{
	Health += Delta;
	UE_LOG(LogTemp, Warning, TEXT("New Health is :%f"), Health);

	OnHealthChanged.Broadcast(nullptr, this, Health, Delta);

	return true;
}


