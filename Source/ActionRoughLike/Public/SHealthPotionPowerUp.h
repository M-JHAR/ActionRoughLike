// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPowerUpBase.h"
#include "SHealthPotionPowerUp.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROUGHLIKE_API ASHealthPotionPowerUp : public ASPowerUpBase
{
	GENERATED_BODY()
	

protected:

	FTimerHandle TimerHande_ItemUsed;

	UPROPERTY(EditDefaultsOnly)
	float HealAmount;

	UPROPERTY(EditDefaultsOnly)
	float ReUseTime;

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

	void ReactiveItem_TimeElapsed();

	void DeactiveActorComponents();

	void ReactiveActorComponents();

public:

	ASHealthPotionPowerUp();
};
