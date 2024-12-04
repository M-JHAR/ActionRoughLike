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
#include "SGameplayFunctionLibrary.h"
#include "SActionComponent.h"
#include "GameplayTagContainer.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ASMagicProjectile::ASMagicProjectile()
{
	//MovementComp->InitialSpeed = 2000.0f;

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OnActorOvlerlap);
	
	InitialLifeSpan = 10.0f;

	DamageAmount = 20.0f;

}

void ASMagicProjectile::OnActorOvlerlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && GetInstigator() != OtherActor)
	{
		// Now AI cannot Damage Another AI
		//if (GetInstigator()->GetClass() == OtherActor->GetClass()) return;


		USActionComponent* ActionComp = OtherActor->GetComponentByClass<USActionComponent>();

		if (ActionComp && ActionComp->ActiveGameplayTags.HasTag(ParryTag))
		{
			MovementComp->Velocity = -MovementComp->Velocity;

			SetInstigator(Cast<APawn>(OtherActor));
			return;
		}

		if (USGameplayFunctionLibrary::ApplyDirectionalDamage(GetInstigator(), OtherActor, DamageAmount, SweepResult))
		{
			Explode();
		}


	}

}
