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
#include "DrawDebugHelpers.h"

// Sets default values
ASMagicProjectile::ASMagicProjectile()
{
	MovementComp->InitialSpeed = 2000.0f;

	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ASMagicProjectile::OnActorOvlerlap);

	AudioComp = CreateDefaultSubobject<UAudioComponent>("AudioComp");
	AudioComp->SetupAttachment(RootComponent);
}

void ASMagicProjectile::BeginPlay()
{
	Super::BeginPlay();

	APawn* MyPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (ensure(MyPawn))
	{
		if (MyPawn == GetInstigator())
		{
			ACharacter* MyPlayer = Cast<ACharacter>(MyPawn);

			FVector HandLocation = MyPlayer->GetMesh()->GetSocketLocation("Muzzle_01");
			FRotator HandRotation = MyPlayer->GetMesh()->GetSocketRotation("Muzzle_01");

			UGameplayStatics::SpawnEmitterAttached(MuzzleFlashVFX, MyPlayer->GetRootComponent(), NAME_None, HandLocation, HandRotation, EAttachLocation::Type::KeepWorldPosition);

			FVector PlayerLocation = MyPlayer->GetActorLocation();
			UGameplayStatics::PlayWorldCameraShake(GetWorld(), CameraShakeClass, PlayerLocation, 0.0f, 2000.0f);


			//DrawDebugSphere(GetWorld(), PlayerLocation, 2000.0f,16,FColor::Green,false,10,0,2);
		}
	}
}

// Execute OnActorHit 
void ASMagicProjectile::Explode_Implementation()
{
	UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
	Super::Explode_Implementation();
}

void ASMagicProjectile::OnActorOvlerlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && GetInstigator() != OtherActor)
	{
		USAttributeComponent* AttributeComp = Cast<USAttributeComponent>(OtherActor->GetComponentByClass(USAttributeComponent::StaticClass()));

		if (AttributeComp)
		{
			AttributeComp->ApplyHealthChange(-DamageAmount);

			UE_LOG(LogTemp, Warning, TEXT("Is Hit"));

			Destroy();
		}

	}
	//if(GetInstigator())


}
