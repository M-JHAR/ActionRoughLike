// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SPowerUpBase.h"
#include "SCoinPowerup.generated.h"


class UStaticMeshComponent;

UCLASS()
class ACTIONROUGHLIKE_API ASCoinPowerup : public ASPowerUpBase
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Powerup")
	UStaticMeshComponent* MeshComp;

	void Interact_Implementation(APawn* InstigatorPawn) override;
public:	

	ASCoinPowerup();


};
