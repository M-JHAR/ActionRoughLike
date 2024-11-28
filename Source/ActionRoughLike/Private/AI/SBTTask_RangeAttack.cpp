// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/SBTTask_RangeAttack.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "GameFramework/Character.h"
#include "SAttributeComponent.h"

USBTTask_RangeAttack::USBTTask_RangeAttack()
{
	MaxProjOffset = 2.0f;
}
EBTNodeResult::Type USBTTask_RangeAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	AAIController* MyController = OwnerComp.GetAIOwner();
	if (ensure(MyController))
	{
		ACharacter* MyPawn = Cast<ACharacter>(MyController->GetPawn());
		if (MyPawn == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		FVector MuzzleLocation = MyPawn->GetMesh()->GetSocketLocation("Muzzle_01");

		AActor* TagetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("TargetActor"));
		if (TagetActor == nullptr)
		{
			return EBTNodeResult::Failed;
		}

		if (USAttributeComponent::IsActorAlive(TagetActor) == false)
		{
			return EBTNodeResult::Failed;
		}

		FVector Direction = TagetActor->GetActorLocation() - MuzzleLocation;
		FRotator MuzzleRotation = Direction.Rotation();

		MuzzleRotation.Pitch += FMath::RandRange(0.0f, MaxProjOffset);
		MuzzleRotation.Yaw += FMath::RandRange(-MaxProjOffset, MaxProjOffset);


		FActorSpawnParameters Params;
		Params.Instigator = MyPawn;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		AActor* NewProj = GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation, MuzzleRotation, Params);

		return NewProj ? EBTNodeResult::Succeeded : EBTNodeResult::Failed;
	}

	return EBTNodeResult::Failed;
}


