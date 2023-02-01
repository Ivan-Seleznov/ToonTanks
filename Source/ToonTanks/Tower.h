// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaTime) override;
	void HandleDestructions();
protected:
	virtual void BeginPlay() override;
private:
	class ATank* Tank;

	UPROPERTY(EditDefaultsOnly,Category="Combat")
		float Range = 200;

	FTimerHandle FireRateTimerHandle;
	void CheckFireCondition();
	float FireRate = 2;

	bool CheckFireRange();
};
