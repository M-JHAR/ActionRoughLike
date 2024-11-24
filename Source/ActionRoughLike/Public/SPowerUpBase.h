// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGameplayInterface.h"
#include "SPowerUpBase.generated.h"


class USphereComponent;

UCLASS(ABSTRACT)
class ACTIONROUGHLIKE_API ASPowerUpBase : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditAnywhere, Category = "PowerUp");
	float RespawnTime;

	FTimerHandle TimerHande_RespawnTimer;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USphereComponent* SphereComp;

	UFUNCTION()
	void ShowPowerUp();

	void HideAndCooldownPowerUp();

	void SetPowerUpState(bool bNewIsActive);

public:

	void Interact_Implementation(APawn* InstigatorPawn) override;

public:	
	ASPowerUpBase();

};
