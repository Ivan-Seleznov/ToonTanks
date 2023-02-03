// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePowerUp.h"
#include "SpeedUp.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ASpeedUp : public ABasePowerUp
{
	GENERATED_BODY()
protected:
	virtual void Activate(ATank* Tank) override;
private:
	UPROPERTY(EditAnywhere)
		float SpeedBoost = 100;
};
