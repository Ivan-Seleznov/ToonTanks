// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthUp.h"
#include "Tank.h"
#include "HealthComponent.h"

void AHealthUp::Activate(ATank* Tank)
{
	Super::Activate(Tank);

	if (UHealthComponent* health = Cast<UHealthComponent>
		(Tank->GetComponentByClass(UHealthComponent::StaticClass())))
	{
		if (health->GetHealth() == health->GetMaxHealth())
			return;

		health->SetHealth(health->GetHealth() + HealthBoost);
		DestroyPowerUp();
	}
}

