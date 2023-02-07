// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePowerUp.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include <Components/CapsuleComponent.h>

// Sets default values
ABasePowerUp::ABasePowerUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	RootComponent = CapsuleComp;

	MainMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Main Mesh"));
	MainMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ABasePowerUp::BeginPlay()
{
	Super::BeginPlay();
	CapsuleComp->OnComponentBeginOverlap.AddDynamic(this, &ABasePowerUp::BeginOverlap);
}

ATank* ABasePowerUp::GetPawn()
{
	return Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));
}

void ABasePowerUp::Activate(ATank* Tank)
{
	if (PickupSound)
		UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());
	if (PickupParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, PickupParticles, GetActorLocation(), GetActorRotation());
	}
}
void ABasePowerUp::DestroyPowerUp() {
	Destroy();
}
// Called every frame
void ABasePowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void ABasePowerUp::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	UE_LOG(LogTemp, Warning, TEXT("Overlap"));
	ATank* Tank = GetPawn();
	if (OtherActor == Tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Activate"));
		Activate(Tank);
	}
}

