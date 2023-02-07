// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedUp.h"
#include "Tank.h"
#include "Components/CapsuleComponent.h"


void ASpeedUp::Activate(ATank* Tank)
{
	Super::Activate(Tank);
	if (!Tank->IsBoost())
	{
		Tank->SetUnderBoost(true);

		UE_LOG(LogTemp, Warning, TEXT("Speed Boost"));

		StartSpeed = Tank->GetSpeed();
		Tank->SetSpeed(StartSpeed + SpeedBoost);

		GetWorld()->GetTimerManager().SetTimer(SpeedBoostTimer, this, &ASpeedUp::SetToStartSpeed, BoostTime,false);
		UE_LOG(LogTemp, Warning, TEXT("Speed Boost"));

		CapsuleComp->DestroyComponent();
		MainMesh->DestroyComponent();
	}
}
void ASpeedUp::SetToStartSpeed() {
	if (ATank* Tank = GetPawn())
	{
		Tank->SetSpeed(StartSpeed);

		Tank->SetUnderBoost(false);
		DestroyPowerUp();
		UE_LOG(LogTemp, Warning, TEXT("Normal speed"));
	}
}
