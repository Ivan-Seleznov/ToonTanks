// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include <Kismet/GameplayStatics.h>
#include "TimerManager.h"
#include "BasePowerUp.h"

void ATower::BeginPlay() {
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimerHandle,this,&ATower::CheckFireCondition,FireRate,true);
}
void ATower::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (CheckFireRange())
		RotateTurret(Tank->GetActorLocation());
}
void ATower::CheckFireCondition() {
	if (CheckFireRange() && Tank && Tank->bAlive)
		Fire();	
}
bool ATower::CheckFireRange() {
	if (Tank)
	{
		float distance = FVector::Distance(GetActorLocation(), Tank->GetActorLocation());
		if (distance <= Range)
			return true;
	}
	return false;
}

void ATower::SpawnPowerUps()
{
	FVector Location = GetActorLocation();
	float i = 0.5;
	float yValue = 0;

	FVector Offset;
	for (auto Item : DroppedPowerUps)
	{
		//Offset = FVector(-GetActorLocation().ForwardVector + i * 100,0, 0);
		if (i >= 1)
			yValue = rand() % 500;

		Offset = Location.ForwardVector + FVector(-(i * 100),yValue, 0);
		UE_LOG(LogTemp,Display,TEXT("ActorLocation: %s | Huy %s"), *GetActorLocation().ToCompactString(), *(GetActorLocation() + Offset).ToCompactString())
		ABasePowerUp* PowerUp = GetWorld()->SpawnActor<ABasePowerUp>(Item, GetActorLocation() + Offset, GetActorRotation());
		
		i++;
	}
}

void ATower::HandleDestructions() {
	Super::HandleDestructions();
	Destroy();
	SpawnPowerUps();
}