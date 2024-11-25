// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "SCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class USInteractionComponent;
class UAnimMontage;
class UParticleSystem;
class USAttributeComponent;


UCLASS()
class ACTIONROUGHLIKE_API ASCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	FName TimeToHitParamName;

	UPROPERTY(VisibleAnywhere, Category = "Effects")
	FName HandSocketName;

	UPROPERTY(EditAnywhere, Category = Attack)
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = Attack)
	TSubclassOf<AActor> BlackholeClass;

	UPROPERTY(EditAnywhere, Category = Attack)
	TSubclassOf<AActor> TeleportClass;

	UPROPERTY(EditAnywhere, Category = Attack)
	UAnimMontage* AttackAnim;

	FTimerHandle TimerHanlde_PrimaryAttack;

	FTimerHandle TimerHanlde_BlackholeAttack;

	FTimerHandle TimerHanlde_Teleport;

	UPROPERTY(EditDefaultsOnly, Category = "Attack")
	float AttackAnimDelay;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* PlayerMapingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveForwardAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* MoveRightAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* PrimaryAttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* BlackholeAttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* TeleportAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputAction* InteractAction;

protected:
	UPROPERTY(VisibleAnywhere, Category = "Component")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	USInteractionComponent* InteractionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Component")
	USAttributeComponent* AttributeComp;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystem* CastingEffect;

	void MoveForward(const FInputActionValue& Value);

	void MoveRight(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void Jump();

	void PrimaryAttack();

	void PrimaryAttack_TimeElapsed();

	void BlackholeAttack();

	void BlackholeAttack_TimeElapsed();

	void Teleport();

	void Teleport_TimeElapsed();

	void PrimaryInteract();

	void SpawnProjectile(const TSubclassOf<AActor>& ToSpawnClass);


	virtual void BeginPlay() override;

	void StartAttackEffect();

	UFUNCTION()
	void OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta);

	virtual void PostInitializeComponents() override;

public:

	ASCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
