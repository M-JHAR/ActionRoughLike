// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SPowerUpBase.h"
#include "SCoinPowerup.generated.h"

UCLASS()
class ACTIONROUGHLIKE_API ASCoinPowerup : public ASPowerUpBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "Credits")
	int32 CreditsAmount;

public:

	void Interact_Implementation(APawn* InstigatorPawn) override;
	
	ASCoinPowerup();


};
