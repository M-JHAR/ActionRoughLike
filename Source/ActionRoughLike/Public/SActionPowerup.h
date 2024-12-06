// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPowerUpBase.h"
#include "SActionPowerup.generated.h"


class USAction;
UCLASS()
class ACTIONROUGHLIKE_API ASActionPowerup : public ASPowerUpBase
{
	GENERATED_BODY()


protected:

	UPROPERTY(EditDefaultsOnly, Category = "Action")
	TSubclassOf<USAction> ActionClass;

public:

	void Interact_Implementation(APawn* InstigatorPawn) override;
	
	ASActionPowerup();
};
