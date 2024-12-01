// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SWorldUserWidget.generated.h"


class USizeBox;
/**
 *
 */
UCLASS()
class ACTIONROUGHLIKE_API USWorldUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta = (BindWidget))
	USizeBox* ParentSizeBox;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:

	UPROPERTY(EditAnywhere, Category = "UI")
	FVector WolrdOffset;

	UPROPERTY(BlueprintReadOnly, Category = "UI", meta = (ExposeOnSpawn = true))
	AActor* AttachedActor;

};
