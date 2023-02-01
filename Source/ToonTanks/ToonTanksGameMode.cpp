// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"
#include "HealthComponent.h"
void AToonTanksGameMode::BeginPlay() {
	Super::BeginPlay();
	HandleGameStart();
}
void AToonTanksGameMode::ActorDied(AActor* DeadActor) {
	if (DeadActor == Tank)
	{
		Tank->HandleDestructions();
		if (ToonTanksPlayerController)
			ToonTanksPlayerController->SetPlayerEnableState(false);
		GameOver(false);
	}
	else if(ATower* DestroyedTower = Cast<ATower>(DeadActor)){
		DestroyedTower->HandleDestructions();
		TargetTowersCount--;
		if (TargetTowersCount <= 0)
			GameOver(true);
	}
}
void AToonTanksGameMode::HandleGameStart()
{
	TargetTowersCount = GetTargetTowersCount();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	
	StartGame();

	if (ToonTanksPlayerController)
	{
		ToonTanksPlayerController->SetPlayerEnableState(false);
		FTimerHandle PlayerTimerHandle;
		FTimerDelegate PlayerTimerDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController,&AToonTanksPlayerController::SetPlayerEnableState,true);
		GetWorld()->GetTimerManager().SetTimer(PlayerTimerHandle, PlayerTimerDelegate, StartDelay, false);
	}

}

int32 AToonTanksGameMode::GetTargetTowersCount()
{
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(this,ATower::StaticClass(),Towers);
	
	return Towers.Num();
}
