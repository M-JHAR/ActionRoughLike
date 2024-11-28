// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SProjectile.h"
#include "SMagicProjectile.generated.h"

class UAudioComponent;
class USoundBase;
class UParticleSystem;
class UCameraShakeBase;

UCLASS()
class ACTIONROUGHLIKE_API ASMagicProjectile : public ASProjectile
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly)
	float DamageAmount;

	UFUNCTION()
	void OnActorOvlerlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:

	ASMagicProjectile();


};
