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
	if (!GetController())
	{
		return;
	}
	this->ACharacter::Jump();

}

void ASCharacter::PrimaryInteract()
{
	if (InteractionComp)
		InteractionComp->PrimaryInteract();
}

void ASCharacter::PrimaryAttack()
{
	PlayAnimMontage(AttackMove);

	GetWorldTimerManager().SetTimer(TimerHanlde_PrimaryAttack, this, &ASCharacter::PrimaryAttack_TimeElapsed, 0.2f);
}

void ASCharacter::PrimaryAttack_TimeElapsed()
{
	SpawnActorLineTrace(ProjectileClass);
}

void ASCharacter::BlackholeAttack()
{
	PlayAnimMontage(AttackMove);

	GetWorldTimerManager().SetTimer(TimerHanlde_BlackholeAttack, this, &ASCharacter::BlackholeAttack_TimeElapsed, 0.2f);
}

void ASCharacter::BlackholeAttack_TimeElapsed()
{
	SpawnActorLineTrace(BlackholeClass);
}

void ASCharacter::Teleport()
{
	PlayAnimMontage(AttackMove);

	GetWorldTimerManager().SetTimer(TimerHanlde_Teleport, this, &ASCharacter::SpawnTeleport_TimeElapsed, 0.2f);
}

void ASCharacter::SpawnTeleport_TimeElapsed()
{
	SpawnActorLineTrace(TeleportClass);
}

// This is entirely optional, it draws two arrows to visualize rotations of the player
void ASCharacter::Tick(float DeltaTime)
{

}


void ASCharacter::SpawnActorLineTrace(const TSubclassOf<AActor>& ToSpawnClass)
{
	if (GetController())
	{
		TArray<FHitResult> Hits;

		FVector Start = CameraComp->GetComponentLocation();
		FVector End = Start + CameraComp->GetForwardVector() * 4000.0f;
		FVector Target = End;

		FCollisionObjectQueryParams ObjectQueryParams;
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldStatic);
		ObjectQueryParams.AddObjectTypesToQuery(ECC_WorldDynamic);

		GetWorld()->LineTraceMultiByObjectType(Hits, Start, End, ObjectQueryParams);

		for (const FHitResult& Hit : Hits)
		{
			if (AActor* ActorHit = Hit.GetActor())
			{
				Target = Hit.ImpactPoint;
				break;
			}
		}

		FVector HandLocation = GetMesh()->GetSocketLocation("Muzzle_01");

		FRotator ProjectileRot = UKismetMathLibrary::FindLookAtRotation(HandLocation, Target);

		FTransform SpawnTM = FTransform(ProjectileRot, HandLocation);


		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParams.Instigator = this;

		GetWorld()->SpawnActor<AActor>(ToSpawnClass, SpawnTM, SpawnParams);
	}

}
