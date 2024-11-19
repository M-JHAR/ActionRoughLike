// Fill out your copyright notice in the Description page of Project Settings.


#include "STeleportProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SphereComponent.h"

#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"



ASTeleportProjectile::ASTeleportProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	MovementComp->InitialSpeed = 2000.0f;


}

void ASTeleportProjectile::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	SphereComp->OnComponentHit.AddDynamic(this, &ASTeleportProjectile::OnHit);
}

void ASTeleportProjectile::BeginPlay()
{
	Super::BeginPlay();

	//Delay
	if (bOnHit) return;
	GetWorldTimerManager().SetTimer(TimerHande_TeleportProjectile, this, &ASTeleportProjectile::WaitEffectToComplete_TimeElapsed, 0.4f);



}

void ASTeleportProjectile::WaitEffectToComplete_TimeElapsed()
{
	if (bOnHit) return;

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExitTeleportEffect, GetActorTransform(), true);
	MovementComp->Deactivate();
	EffectComp->Deactivate();

	if (AActor* MyPlayer = GetInstigator())
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), EnterTeleportEffect, MyPlayer->GetActorTransform(), true);
	//Delay
	GetWorldTimerManager().SetTimer(TimerHande_TeleportProjectile, this, &ASTeleportProjectile::DoTeleport_TimeElapsed, 0.25f);


}

void ASTeleportProjectile::DoTeleport_TimeElapsed()
{
	if (bOnHit) return;

	AActor* MyPlayer = GetInstigator();
	if (!MyPlayer) return;

	FVector ProjectileLoc = GetActorLocation();
	FRotator ProjectileRot = GetActorRotation();


	MyPlayer->TeleportTo(ProjectileLoc, ProjectileRot);
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExitTeleportEffect, GetActorTransform(), true);

	Destroy();
}

void ASTeleportProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AActor* MyPlayer = GetInstigator();
	if (!MyPlayer) return;

	if (OtherActor == MyPlayer) return;

	bOnHit = true;

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExitTeleportEffect, GetActorTransform(), true);
	MovementComp->Deactivate();
	EffectComp->Deactivate();


	FVector ProjectileLoc = GetActorLocation();
	FRotator ProjectileRot = GetActorRotation();


	FVector UpVec = MyPlayer->GetActorUpVector() * 50;

	FTransform ProjectileTransform = FTransform(ProjectileRot, ProjectileLoc + UpVec);

	MyPlayer->SetActorTransform(ProjectileTransform, false ,nullptr,ETeleportType::TeleportPhysics);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExitTeleportEffect, GetActorTransform(), true);

	Destroy();

}
