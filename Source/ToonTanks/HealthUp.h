// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePowerUp.h"
#include "HealthUp.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AHealthUp : public ABasePowerUp
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		float HealthBoost = 20;

protected:
	virtual void Activate(ATank* Tank) override;

};
