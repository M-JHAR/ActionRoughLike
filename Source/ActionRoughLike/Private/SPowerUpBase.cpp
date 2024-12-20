// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerUpBase.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ASPowerUpBase::ASPowerUpBase()
{

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Powerup");
	RootComponent = SphereComp;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(RootComponent);


	RespawnTime = 10.0f;
}

void ASPowerUpBase::Interact_Implementation(APawn* InstigatorPawn)
{
	// logic in derived classes
}

void ASPowerUpBase::ShowPowerUp()
{
	SetPowerUpState(true);
}

void ASPowerUpBase::HideAndCooldownPowerUp()
{
	SetPowerUpState(false);

	FTimerHandle TimerHande_RespawnTimer;
	GetWorldTimerManager().SetTimer(TimerHande_RespawnTimer, this, &ASPowerUpBase::ShowPowerUp, RespawnTime);
}

void ASPowerUpBase::SetPowerUpState(bool bNewIsActive)
{
	SetActorEnableCollision(bNewIsActive);

	RootComponent->SetVisibility(bNewIsActive, true);
}
