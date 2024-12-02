// Fill out your copyright notice in the Description page of Project Settings.


#include "SAction_ProjectileAttack.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"


USAction_ProjectileAttack::USAction_ProjectileAttack()
{
	AttackAnimDelay = 0.2f;
	HandSocketName = "Muzzle_01";
}

void USAction_ProjectileAttack::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	ACharacter* Character = Cast<ACharacter>(Instigator);
	if (ensure(Character))
	{
		Character->PlayAnimMontage(AttackAnim);

		UGameplayStatics::SpawnEmitterAttached(CastingEffect, Character->GetMesh(), HandSocketName, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget);

		FTimerHandle TimerHande_AttackDelay;
		FTimerDelegate Delegate;
		Delegate.BindUObject(this, &USAction_ProjectileAttack::AttackDelay_Elapsed, Character);

		GetWorld()->GetTimerManager().SetTimer(TimerHande_AttackDelay, Delegate, AttackAnimDelay, false);
	}


}
void USAction_ProjectileAttack::AttackDelay_Elapsed(ACharacter* InstigatorCharacter)
{
	if (ensureAlways(ProjectileClass))
	{
		FVector HandLocation = InstigatorCharacter->GetMesh()->GetSocketLocation(HandSocketName);

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = InstigatorCharacter;

		FCollisionShape Shape;
		Shape.SetSphere(20.0f);

		//	Ignore Player
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(InstigatorCharacter);

		FCollisionObjectQueryParams ObjParams;
		ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjParams.AddObjectTypesToQuery(ECC_PhysicsBody);
		ObjParams.AddObjectTypesToQuery(ECC_Pawn);

		FVector TraceStart = InstigatorCharacter->GetPawnViewLocation();  //CameraComp->GetComponentLocation();

		//FVector TraceEnd = TraceStart + (GetControlRotation().Vector() * 5000.0f);
		FVector TraceEnd = TraceStart + (InstigatorCharacter->GetControlRotation().Vector() * 5000.0f);

		FHitResult Hit;
		if (GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, FQuat::Identity, ObjParams, Shape, Params))
		{
			TraceEnd = Hit.ImpactPoint;
		}


		//FRotator ProjRotation = UKismetMathLibrary::FindLookAtRotation(HandLocation, TraceEnd);
		FRotator ProjRotation = FRotationMatrix::MakeFromX(TraceEnd - HandLocation).Rotator();

		FTransform SpawnTM = FTransform(ProjRotation, HandLocation);
		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
	}
	StopAction(InstigatorCharacter);
}
