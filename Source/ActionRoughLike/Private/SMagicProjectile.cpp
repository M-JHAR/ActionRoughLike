// Fill out your copyright notice in the Description page of Project Settings.


#include "SMagicProjectile.h"
#include "SProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "SAttributeComponent.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"


// Sets default values
ASMagicProjectile::ASMagicProjectile()
{
	MovementComp->InitialSpeed = 2000.0f;

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OnActorOvlerlap);
}

void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Execute OnActorHit 
void ASMagicProjectile::Explode_Implementation()
{
	Super::Explode_Implementation();
}

void ASMagicProjectile::OnActorOvlerlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && GetInstigator() != OtherActor)
	{
		// Now AI cannot Damage Another AI
		if (GetInstigator()->GetClass() == OtherActor->GetClass()) return;

		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));

		if (AttributeComp)
		{
			AttributeComp->ApplyHealthChange(-DamageAmount);

			UE_LOG(LogTemp, Warning, TEXT("Is Hit"));

			Super::Explode_Implementation();
			//Destroy();
		}

		
	}

}
