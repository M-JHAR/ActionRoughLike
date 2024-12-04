// Fill out your copyright notice in the Description page of Project Settings.


#include "SActionEffect.h"
#include "SActionComponent.h"

USActionEffect::USActionEffect()
{
	Period = 1.0f;

	Duration = 3.0f;

	bAutoStart = true;
}

void USActionEffect::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	if (Duration > 0.0f)
	{
		FTimerDelegate Delegate;
		Delegate.BindUObject(this, &USActionEffect::StopAction, Instigator);

		GetWorld()->GetTimerManager().SetTimer(DurationHandle, Delegate, Duration, false);
	}
	if (Period > 0.0f)
	{
		FTimerDelegate Delegate;
		Delegate.BindUObject(this, &USActionEffect::ExecutePeriodicEffect, Instigator);;

		GetWorld()->GetTimerManager().SetTimer(PeroidHandle, Delegate, Period, true);
	}

}

void USActionEffect::StopAction_Implementation(AActor* Instigator)
{
	if (GetWorld()->GetTimerManager().GetTimerRemaining(PeroidHandle) < KINDA_SMALL_NUMBER)
	{
		ExecutePeriodicEffect(Instigator);
	}

	Super::StopAction_Implementation(Instigator);

	GetWorld()->GetTimerManager().ClearTimer(DurationHandle);
	GetWorld()->GetTimerManager().ClearTimer(PeroidHandle);

	USActionComponent* Comp = GetOwningComponent();
	if (ensureAlways(Comp))
	{
		Comp->RemoveAction(this);
		
		//GetWorld()->DestroyActor(Cast<AActor>(this));
	}

}

void USActionEffect::ExecutePeriodicEffect_Implementation(AActor* InstigatorActor)
{
	// Logic in  Blueprint
}



