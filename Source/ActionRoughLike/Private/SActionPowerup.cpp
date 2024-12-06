// Fill out your copyright notice in the Description page of Project Settings.


#include "SActionPowerup.h"
#include "SActionComponent.h"
#include "SAction.h"

ASActionPowerup::ASActionPowerup()
{

}


void ASActionPowerup::Interact_Implementation(APawn* InstigatorPawn)
{
	USActionComponent* ActionComp = InstigatorPawn->GetComponentByClass<USActionComponent>();
	if (!ensure(ActionComp))
	{
		return;
	}

	if (!ActionComp->ContainAction("Teleport"))
	{
		ActionComp->AddAction(InstigatorPawn, ActionClass);

		UE_LOG(LogTemp, Warning, TEXT("Action Is Added Correctly"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Action is ALREADY ADDED!"));
	}
}


