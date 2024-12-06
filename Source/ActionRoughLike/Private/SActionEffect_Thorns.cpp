// Fill out your copyright notice in the Description page of Project Settings.


#include "SActionEffect_Thorns.h"
#include "SAttributeComponent.h"
#include "SActionComponent.h"
#include "SGameplayFunctionLibrary.h"

USActionEffect_Thorns::USActionEffect_Thorns()
{
	Duration = 0.0f;

	Period = 0.0f;

	ThornPercentage = 0.4f;

}


void USActionEffect_Thorns::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	if (Duration == 0.0f)
	{
		USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(Instigator);
		if (ensure(AttributeComp))
		{
			AttributeComp->OnHealthChanged.AddDynamic(this, &USActionEffect_Thorns::OnHealthChanged);

		}
	}

}


void USActionEffect_Thorns::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);

	USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(Instigator);
	if (ensure(AttributeComp))
	{
		AttributeComp->OnHealthChanged.RemoveDynamic(this, &USActionEffect_Thorns::OnHealthChanged);

		USActionComponent* ActionComp = GetOwningComponent();
		ActionComp->RemoveAction(this);
	}
}


void USActionEffect_Thorns::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	if (Delta > 0.0f)
	{
		return;
	}

	if (InstigatorActor == GetOwningComponent()->GetOwner())
	{
		return;
	}

	float ThornDamage = -Delta * ThornPercentage;
	
	if (ensure(OwningComp))
	{
		AActor* Player = GetOwningComponent()->GetOwner();
		if (ensure(Player))
		{
			USGameplayFunctionLibrary::ApplyDamage(Player, InstigatorActor, FMath::RoundToInt32(ThornDamage));
			UE_LOG(LogTemp, Warning, TEXT("Thorn Applied"));
		}

	}

}
