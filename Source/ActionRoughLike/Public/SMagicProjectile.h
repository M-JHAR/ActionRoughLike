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
	float DamageAmount = 20.0f;

	UPROPERTY(EditAnywhere,Category = "Shake")
	TSubclassOf<UCameraShakeBase> CameraShakeClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effects")
	UParticleSystem* MuzzleFlashVFX;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Sounds")
	UAudioComponent* AudioComp;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* ImpactSound;


	UFUNCTION()
	void OnActorOvlerlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	virtual void Explode_Implementation() override;

	virtual void BeginPlay() override;

public:

	ASMagicProjectile();


};
