// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "DrawDebugHelpers.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SInteractionComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/SphereComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "SAttributeComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComp");
	SpringArmComp->bUsePawnControlRotation = true;
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
	CameraComp->SetupAttachment(SpringArmComp);

	InteractionComp = CreateDefaultSubobject<USInteractionComponent>("InteractionComp");

	AttributeComp = CreateDefaultSubobject<USAttributeComponent>("AttributeComp");

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;


	AttackAnimDelay = 0.2f;
	TimeToHitParamName = "TimeHit";
	HandSocketName = "Muzzle_01";
}

// Called when the game starts or when spawned
void ASCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(PlayerMapingContext, 0);
		}

	}

}


void ASCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	AttributeComp->OnHealthChanged.AddDynamic(this, &ASCharacter::OnHealthChanged);
}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &ASCharacter::MoveForward);
		EnhancedInputComponent->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &ASCharacter::MoveRight);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ASCharacter::Jump);

		EnhancedInputComponent->BindAction(PrimaryAttackAction, ETriggerEvent::Triggered, this, &ASCharacter::PrimaryAttack);
		EnhancedInputComponent->BindAction(BlackholeAttackAction, ETriggerEvent::Triggered, this, &ASCharacter::BlackholeAttack);
		EnhancedInputComponent->BindAction(TeleportAction, ETriggerEvent::Triggered, this, &ASCharacter::Teleport);

		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ASCharacter::PrimaryInteract);
	}
}


void ASCharacter::MoveForward(const FInputActionValue& Value)
{
	const float DirectionValue = Value.Get<float>();

	if (GetController() && DirectionValue != 0)
	{
		FRotator ControlRot = GetControlRotation();
		ControlRot.Pitch = 0;
		ControlRot.Roll = 0;

		//FVector PlayerForwardVector = GetActorForwardVector();
		AddMovementInput(ControlRot.Vector(), DirectionValue);
	}

}

void ASCharacter::MoveRight(const FInputActionValue& Value)
{
	const float DirectionValue = Value.Get<float>();

	if (GetController() && DirectionValue != 0)
	{
		FRotator ControlRot = GetControlRotation();
		FVector RightVector = FRotationMatrix(ControlRot).GetScaledAxis(EAxis::Y);

		//FVector PlayerRightVector = GetActorRightVector();
		AddMovementInput(RightVector, DirectionValue);
	}
}

void ASCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisValue = Value.Get<FVector2D>();

	if (GetController())
	{
		AddControllerYawInput(LookAxisValue.X);
		AddControllerPitchInput(LookAxisValue.Y);
	}
}

void ASCharacter::Jump()
{
	if (!GetController()) return;

	this->ACharacter::Jump();

}

void ASCharacter::PrimaryInteract()
{
	if (InteractionComp)
		InteractionComp->PrimaryInteract();
}

void ASCharacter::PrimaryAttack()
{
	StartAttackEffect();

	GetWorldTimerManager().SetTimer(TimerHanlde_PrimaryAttack, this, &ASCharacter::PrimaryAttack_TimeElapsed, 0.2f);
}

void ASCharacter::PrimaryAttack_TimeElapsed()
{
	SpawnProjectile(ProjectileClass);
}

void ASCharacter::BlackholeAttack()
{
	StartAttackEffect();

	GetWorldTimerManager().SetTimer(TimerHanlde_BlackholeAttack, this, &ASCharacter::BlackholeAttack_TimeElapsed, 0.2f);
}

void ASCharacter::BlackholeAttack_TimeElapsed()
{
	SpawnProjectile(BlackholeClass);
}

void ASCharacter::Teleport()
{
	StartAttackEffect();

	GetWorldTimerManager().SetTimer(TimerHanlde_Teleport, this, &ASCharacter::Teleport_TimeElapsed, 0.2f);
}

void ASCharacter::Teleport_TimeElapsed()
{
	SpawnProjectile(TeleportClass);
}

void ASCharacter::StartAttackEffect()
{
	PlayAnimMontage(AttackAnim);

	UGameplayStatics::SpawnEmitterAttached(CastingEffect, GetMesh(), HandSocketName, FVector::ZeroVector, FRotator::ZeroRotator,
		EAttachLocation::SnapToTarget);
}

void ASCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void ASCharacter::SpawnProjectile(const TSubclassOf<AActor>& ClassToSpawn)
{
	if (ensureAlways(ClassToSpawn))
	{
		FVector HandLocation = GetMesh()->GetSocketLocation(HandSocketName);

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;

		FCollisionShape Shape;
		Shape.SetSphere(20.0f);

		//	Ignore Player
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);

		FCollisionObjectQueryParams ObjParams;
		ObjParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjParams.AddObjectTypesToQuery(ECC_WorldDynamic);
		ObjParams.AddObjectTypesToQuery(ECC_PhysicsBody);
		ObjParams.AddObjectTypesToQuery(ECC_Pawn);

		FVector TraceStart = CameraComp->GetComponentLocation();

		//FVector TraceEnd = TraceStart + (GetControlRotation().Vector() * 5000.0f);
		FVector TraceEnd = TraceStart + (CameraComp->GetForwardVector() * 5000.0f);

		FHitResult Hit;
		if (GetWorld()->SweepSingleByObjectType(Hit, TraceStart, TraceEnd, FQuat::Identity, ObjParams, Shape, Params))
		{
			TraceEnd = Hit.ImpactPoint;
		}


		//FRotator ProjRotation = UKismetMathLibrary::FindLookAtRotation(HandLocation, TraceEnd);
		FRotator ProjRotation = FRotationMatrix::MakeFromX(TraceEnd - HandLocation).Rotator();

		FTransform SpawnTM = FTransform(ProjRotation, HandLocation);
		GetWorld()->SpawnActor<AActor>(ClassToSpawn, SpawnTM, SpawnParams);


	}
}

void ASCharacter::OnHealthChanged(AActor* InstigatorActor, USAttributeComponent* OwningComp, float NewHealth, float Delta)
{
	// Nerf - damage etc
	if (Delta < 0.0f)
	{
		GetMesh()->SetScalarParameterValueOnMaterials(TimeToHitParamName, GetWorld()->TimeSeconds);

		FVector RedColor = FVector(255, 0, 0);
		GetMesh()->SetVectorParameterValueOnMaterials("HitColor", RedColor);
	}
	// Buffs - heal etc
	else
	{
		UMeshComponent* MeshComp = Cast<UMeshComponent>(GetComponentByClass(UMeshComponent::StaticClass()));
		MeshComp->SetScalarParameterValueOnMaterials(TimeToHitParamName, GetWorld()->TimeSeconds);

		FVector GreenColor = FVector(0, 255, 0);
		MeshComp->SetVectorParameterValueOnMaterials("HitColor", GreenColor);

	}

	// Player Is Dead Stop Moving
	if (NewHealth <= 0.0f && Delta < 0.0f)
	{
		APlayerController* PC = Cast<APlayerController>(GetController());
		DisableInput(PC);
	}
}
