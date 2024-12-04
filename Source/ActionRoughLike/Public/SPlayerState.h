// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCreditsChange, ASPlayerState*, PlayerState, float, NewCredit, float, Delta);
/**
 *
 */
UCLASS()
class ACTIONROUGHLIKE_API ASPlayerState : public APlayerState
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Credits")
	int32 Credits;

public:

	ASPlayerState();

	UFUNCTION(BlueprintCallable, Category = "Credits")
	void AddCredits(int32 Delta);

	UFUNCTION(BlueprintCallable, Category = "Credits")
	bool RemoveCredits(int32 Delta);

	UFUNCTION(BlueprintCallable, Category = "Credits")
	int32 GetCredits() const;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnCreditsChange OnCreditsChange;

};
