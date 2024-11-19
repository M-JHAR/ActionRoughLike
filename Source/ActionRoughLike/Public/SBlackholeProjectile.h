// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SProjectile.h"
#include "SBlackholeProjectile.generated.h"

class UParticleSystemComponent;
class USphereComponent;
class URadialForceComponent;
class UProjectileMovementComponent;

UCLASS()
class ACTIONROUGHLIKE_API ASBlackholeProjectile : public ASProjectile
{
	GENERATED_BODY()
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	URadialForceComponent* RadialComp;


public:	
	// Sets default values for this actor's properties
	ASBlackholeProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
