// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SProjectile.h"
#include "STeleportProjectile.generated.h"


class UParticleSystem;

UCLASS()
class ACTIONROUGHLIKE_API ASTeleportProjectile : public ASProjectile
{
	GENERATED_BODY()

protected:
	bool bOnHit;

	FTimerHandle TimerHande_TeleportProjectile;

	UPROPERTY(EditAnywhere);
	UParticleSystem* ExitTeleportEffect;

	UPROPERTY(EditAnywhere);
	UParticleSystem* EnterTeleportEffect;


protected:

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void DoTeleport_TimeElapsed();

	void WaitEffectToComplete_TimeElapsed();


	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;


public:

	ASTeleportProjectile();

	

	
};
