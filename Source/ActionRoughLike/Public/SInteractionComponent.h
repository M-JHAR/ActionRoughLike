// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SInteractionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ACTIONROUGHLIKE_API USInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void PrimaryInteract();

protected:
	virtual void BeginPlay() override;

public:	
	USInteractionComponent();


		
};
