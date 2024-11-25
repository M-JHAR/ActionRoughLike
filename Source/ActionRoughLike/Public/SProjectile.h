// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SProjectile.generated.h"


class USphereComponent;
class UProjectileMovementComponent;
class UParticleSystemComponent;
class UParticleSystem;
class USoundBase;
class UAudioComponent;
class UCameraShakeBase;

UCLASS(ABSTRACT)
class ACTIONROUGHLIKE_API ASProjectile : public AActor
{
	GENERATED_BODY()

protected:

	float ImpactShakeInnerRadius;

	float ImapctShakeOuterRadius;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* ImpactVFX;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	UParticleSystemComponent* EffectComp;

	UPROPERTY(EditAnywhere, Category = "Shake")
	TSubclassOf<UCameraShakeBase> ImpactShake;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sounds")
	UAudioComponent* AudioComp;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* ImpactSound;



	UFUNCTION()
	virtual void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Explode();

	virtual void PostInitializeComponents() override;

public:

	ASProjectile();

};
