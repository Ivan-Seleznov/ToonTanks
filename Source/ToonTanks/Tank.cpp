// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

ATank::ATank() {
	SpringComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>((TEXT("Camera")));
	CameraComp->SetupAttachment(SpringComp);
}


void ATank::BeginPlay()
{
	Super::BeginPlay();
	PlayerControllerRef =  Cast<APlayerController>(GetController());
}
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PlayerControllerRef)
	{
		FHitResult HitResult;
		PlayerControllerRef->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 20, 12, FColor::Green);

		RotateTurret(HitResult.ImpactPoint);
	}
}
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);

	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}
void ATank::Move(float Value) {
	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

	FVector DeltaLocation = FVector::ZeroVector;
	DeltaLocation.X = Value * DeltaTime * Speed;
	AddActorLocalOffset(DeltaLocation,true);

	//UE_LOG(LogTemp, Warning, TEXT("MOVE: %f | DeltaLocation.X: %f"), Value, DeltaLocation.X);
}
void ATank::Turn(float Value) {

	float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
	
	FRotator DeltaRotator = FRotator::ZeroRotator;
	DeltaRotator.Yaw = Value * DeltaTime * TurnRate;
	AddActorLocalRotation(DeltaRotator);
}
void ATank::HandleDestructions() {
	Super::HandleDestructions();
	//Destroy();
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	bAlive = false;
}



