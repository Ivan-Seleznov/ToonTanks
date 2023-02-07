// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePowerUp.generated.h"

UCLASS()
class TOONTANKS_API ABasePowerUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABasePowerUp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class ATank* GetPawn();

	class UCapsuleComponent* TriggerComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UCapsuleComponent* CapsuleComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* MainMesh;
	
	virtual void Activate(ATank* Tank);

	void DestroyPowerUp();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, Category = "Effects")
		class USoundBase* PickupSound;

	UPROPERTY(EditAnywhere, Category = "Effects")
		class UParticleSystem* PickupParticles;
};
