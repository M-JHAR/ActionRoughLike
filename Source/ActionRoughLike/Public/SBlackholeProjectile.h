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
	
	UPROPERTY(EditDefaultsOnly)
	float ProjLifeDuration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	URadialForceComponent* RadialComp;

	FTimerHandle TimerHande_DelayedLifeSpan;

protected:

	UFUNCTION()
	void OnActorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void BeginPlay() override;
	
	virtual void PostInitializeComponents() override;

	void DestroyActor_FinishedLifeSpan();

public:	

	ASBlackholeProjectile();

};
