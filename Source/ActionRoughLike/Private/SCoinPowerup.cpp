// Fill out your copyright notice in the Description page of Project Settings.


#include "SCoinPowerup.h"
#include "Components/StaticMeshComponent.h"
#include "SPlayerState.h"

ASCoinPowerup::ASCoinPowerup()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(RootComponent);

}

void ASCoinPowerup::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn)) return;

	ASPlayerState* PlayerState = InstigatorPawn->GetPlayerState<ASPlayerState>();

	if (ensure(PlayerState))
	{
		PlayerState->GrantCredit(CreditAmount);

		HideAndCooldownPowerUp();
	}
}

