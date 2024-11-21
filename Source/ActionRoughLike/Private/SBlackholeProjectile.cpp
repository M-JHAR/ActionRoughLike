// Fill out your copyright notice in the Description page of Project Settings.


#include "SBlackholeProjectile.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "SProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ASBlackholeProjectile::ASBlackholeProjectile()
{
	ProjLifeDuration = 5.0f;

	MovementComp->InitialSpeed = 1000.0f;

	RadialComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialComp"));
	RadialComp->SetupAttachment(RootComponent);
}

void ASBlackholeProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASBlackholeProjectile::OnActorBeginOverlap);
}

void ASBlackholeProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TimerHande_DelayedLifeSpan, this, &ASBlackholeProjectile::DestroyActor_FinishedLifeSpan, ProjLifeDuration);
}

void ASBlackholeProjectile::DestroyActor_FinishedLifeSpan()
{
	Destroy();
}

void ASBlackholeProjectile::OnActorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ensure(OtherActor))
	{
		if (OtherComp->IsSimulatingPhysics())
		{
			OtherActor->Destroy();
		}
	}
}
