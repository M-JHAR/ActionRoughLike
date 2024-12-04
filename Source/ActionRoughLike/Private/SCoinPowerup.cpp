// Fill out your copyright notice in the Description page of Project Settings.


#include "SCoinPowerup.h"
#include "Components/StaticMeshComponent.h"
#include "SPlayerState.h"

ASCoinPowerup::ASCoinPowerup()
{
	CreditsAmount = 80;
}

void ASCoinPowerup::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))
	{
		return;
	}

	if (ASPlayerState* PlayerState = InstigatorPawn->GetPlayerState<ASPlayerState>())
	{
		PlayerState->AddCredits(CreditsAmount);

		HideAndCooldownPowerUp();
	}
}

