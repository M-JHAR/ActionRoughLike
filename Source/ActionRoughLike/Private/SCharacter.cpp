// Fill out your copyright notice in the Description page of Project Settings.


#include "SCharacter.h"
#include "DrawDebugHelpers.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

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

	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;
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

void ASCharacter::PrimaryAttack()
{
	if (GetController())
	{
		FVector HandLocation= GetMesh()->GetSocketLocation("Muzzle_01");

		FTransform SpawnTM = FTransform(GetControlRotation(), HandLocation);

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		GetWorld()->SpawnActor<AActor>(ProjectileClass, SpawnTM, SpawnParams);
	}

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


// This is entirely optional, it draws two arrows to visualize rotations of the player
void ASCharacter::Tick(float DeltaTime)
{
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
		EnhancedInputComponent->BindAction(PrimaryAttackAction, ETriggerEvent::Triggered, this, &ASCharacter::PrimaryAttack);
	}
}

