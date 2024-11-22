// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SGameplayInterface.h"
#include "SPowerUpBase.generated.h"


class UStaticMeshComponent;
class USphereComponent;

UCLASS(ABSTRACT)
class ACTIONROUGHLIKE_API ASPowerUpBase : public AActor, public ISGameplayInterface
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* MeshComp;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USphereComponent* SphereComp;

public:	
	ASPowerUpBase();

};
