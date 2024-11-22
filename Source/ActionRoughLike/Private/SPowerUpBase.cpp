// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerUpBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"


// Sets default values
ASPowerUpBase::ASPowerUpBase()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	RootComponent = MeshComp;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetupAttachment(MeshComp);
	
}

//void ASPowerUpBase::Interact_Implementation(APawn* InstigatorPawn)
//{
//	if (ensure(InstigatorPawn))
//	{
//		UE_LOG(LogTemp, Warning, TEXT("Hello World"));
//
//	}
//	
//}
//
//void ASPowerUpBase::UsePowerUp()
//{
//
//}