// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STargetDummy.generated.h"

class USAttributeComponent;
class UStaticMeshComponent;

UCLASS()
class ACTIONROUGHLIKE_API ASTargetDummy : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere,  Category = "Component")
	USAttributeComponent* AttributeComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* MeshComp;


public:
	// Sets default values for this actor's properties
	ASTargetDummy();

	virtual void PostInitializeComponents() override;

protected:

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);


};
