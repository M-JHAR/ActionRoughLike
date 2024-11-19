// Fill out your copyright notice in the Description page of Project Settings.


#include "SBlackholeProjectile.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "SProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ASBlackholeProjectile::ASBlackholeProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MovementComp->InitialSpeed = 1000.0f;

	RadialComp = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialComp"));
	RadialComp->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void ASBlackholeProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASBlackholeProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

