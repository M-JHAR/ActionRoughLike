// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPowerUpBase.h"
#include "SHealthPotionPowerUp.generated.h"

class UStaticMeshComponent;

UCLASS()
class ACTIONROUGHLIKE_API ASHealthPotionPowerUp : public ASPowerUpBase
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere, Category = "HealthPotion")
	float HealAmount;

	UPROPERTY(EditAnywhere, Category = "HealthPotion")
	int32 CreditCost;

	void Interact_Implementation(APawn* InstigatorPawn) override;

public:

	ASHealthPotionPowerUp();
};
