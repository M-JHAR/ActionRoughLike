// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SProjectile.h"
#include "SMagicProjectile.generated.h"

UCLASS()
class ACTIONROUGHLIKE_API ASMagicProjectile : public ASProjectile
{
	GENERATED_BODY()
	
protected:

	UFUNCTION()
	void OnActorOvlerlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	virtual void BeginPlay() override;

public:	

	ASMagicProjectile();


};
