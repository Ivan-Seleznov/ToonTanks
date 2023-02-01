// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include <Kismet/GameplayStatics.h>
#include "TimerManager.h"

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
void ATower::HandleDestructions() {
	Super::HandleDestructions();
	Destroy();
}