// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"

ASPlayerState::ASPlayerState()
{
	TotalCredits = 0.0f;
}

bool ASPlayerState::GrantCredit(float Amount)
{
	TotalCredits += Amount;

	OnCreditChange.Broadcast(TotalCredits, Amount);
	return true;
}

bool ASPlayerState::CostCredit(float Amount)
{
	bool bResult = CanCostCredit(Amount);
	if (bResult)
	{
		TotalCredits -= Amount;

		OnCreditChange.Broadcast(TotalCredits, Amount);
	}
	return bResult;
}

float ASPlayerState::GetCredit() const
{
	return TotalCredits;
}

bool ASPlayerState::CanCostCredit(float AmountToCost) const
{
	return FMath::IsNearlyEqual(TotalCredits, AmountToCost) || (TotalCredits > AmountToCost);

}

