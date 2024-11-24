// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerUpBase.h"
#include "Components/SphereComponent.h"


// Sets default values
ASPowerUpBase::ASPowerUpBase()
{

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Powerup");
	RootComponent = SphereComp;

	RespawnTime = 10.0f;

}
void ASPowerUpBase::Interact_Implementation(APawn* InstigatorPawn)
{
	// logic in derivved classes
}

void ASPowerUpBase::ShowPowerUp()
{
	SetPowerUpState(true);
}

void ASPowerUpBase::HideAndCooldownPowerUp()
{
	SetPowerUpState(false);

	GetWorldTimerManager().SetTimer(TimerHande_RespawnTimer, this, &ASPowerUpBase::ShowPowerUp, RespawnTime);
}

void ASPowerUpBase::SetPowerUpState(bool bNewIsActive)
{
	SetActorEnableCollision(bNewIsActive);

	RootComponent->SetVisibility(bNewIsActive, true);
}
