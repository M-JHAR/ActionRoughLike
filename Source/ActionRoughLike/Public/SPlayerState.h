// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCreditChange, float, TotalCredits, float, Amount);
/**
 * 
 */
UCLASS()
class ACTIONROUGHLIKE_API ASPlayerState : public APlayerState
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(BlueprintReadOnly, Category = "PlayerState")
	float TotalCredits;

	UPROPERTY(BlueprintAssignable)
	FOnCreditChange OnCreditChange;

	bool CanCostCredit(float AmountToCost) const;
public:

	ASPlayerState();

	UFUNCTION(BlueprintCallable, Category = "PlayerState")
	bool GrantCredit(float Amount);

	UFUNCTION(BlueprintCallable, Category = "PlayerState")
	bool CostCredit(float Amount);
	
	UFUNCTION(BlueprintCallable, Category = "PlayerState")
	float GetCredit() const;
	

	
};
