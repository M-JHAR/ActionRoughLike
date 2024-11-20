// Fill out your copyright notice in the Description page of Project Settings.


#include "STeleportProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"

#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/FastReferenceCollector.h"

ASTeleportProjectile::ASTeleportProjectile()
{

	TeleportDelay = 0.2f;
	DetonateDelay = 0.2f;

	MovementComp->InitialSpeed = 6000.0f;


}

void ASTeleportProjectile::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EnterTeleportEffect, GetInstigator()->GetActorTransform());

	GetWorldTimerManager().SetTimer(TimerHande_DelayedDetonate, this, &ASTeleportProjectile::Explode, DetonateDelay);

}

void ASTeleportProjectile::Explode_Implementation()
{
	GetWorldTimerManager().ClearTimer(TimerHande_DelayedDetonate);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactVFX, GetActorTransform());

	EffectComp->DeactivateSystem();

	MovementComp->StopMovementImmediately();
	SetActorEnableCollision(false);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EnterTeleportEffect, GetActorTransform());

	FTimerHandle TimerHande_DelayedTeleport;
	GetWorldTimerManager().SetTimer(TimerHande_DelayedTeleport, this, &ASTeleportProjectile::TeleportInstigator, TeleportDelay);
}

void ASTeleportProjectile::TeleportInstigator()
{
	AActor* ActorToTeleport = GetInstigator();
	if (ensure(ActorToTeleport))
	{
		ActorToTeleport->TeleportTo(GetActorLocation(), ActorToTeleport->GetActorRotation(), false, false);

		Destroy();
	}
}
