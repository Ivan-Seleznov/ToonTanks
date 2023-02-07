// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();
	virtual void Tick(float DeltaTime) override;
	void HandleDestructions();

	APlayerController* GetPlayerController() const { return PlayerControllerRef; }


	bool bAlive = true;

	void SetSpeed(float sp) { Speed = sp; }
	float GetSpeed() { return Speed; }

	UFUNCTION(BlueprintCallable)
		bool IsBoost() { return UndBoost; }

	void SetUnderBoost(bool boost) { UndBoost = boost; }
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
		class UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		class USpringArmComponent* SpringComp;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
		float Speed = 500;

	UPROPERTY(VisibleAnywhere, Category = "Movement")
		float TurnRate = 70;

	void Move(float Value);
	void Turn(float Value);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	APlayerController* PlayerControllerRef;

	bool UndBoost;
};
