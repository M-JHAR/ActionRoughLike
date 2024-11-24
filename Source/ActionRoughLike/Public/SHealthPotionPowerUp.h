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

	UPROPERTY(EditAnywhere, Category = "PowerUp")
	float HealAmount;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* MeshComp;

	virtual void Interact_Implementation(APawn* InstigatorPawn) override;

public:

	ASHealthPotionPowerUp();
};
