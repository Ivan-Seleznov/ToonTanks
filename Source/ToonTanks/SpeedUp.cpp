// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedUp.h"
#include "Tank.h"

void ASpeedUp::Activate(ATank* Tank)
{
	Super::Activate(Tank);
	Tank->SetSpeed(Tank->GetSpeed() + SpeedBoost);
	DestroyPowerUp();
}
