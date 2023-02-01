// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include <Kismet/GameplayStatics.h>
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Component"));
	MovementComponent->MaxSpeed = 1300;
	MovementComponent->InitialSpeed = 1300;
	//ProjectileMesh->SetupAttachment(RootComponent);
	MovingProjectileParticles = CreateDefaultSubobject<UParticleSystemComponent>("MovingProjectile Particles");
	MovingProjectileParticles->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	if(LaunchSound)
		UGameplayStatics::PlaySoundAtLocation(this, LaunchSound, GetActorLocation());
	if (HitCameraShakeClass)
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	AActor* MyOwner = GetOwner();
	if (MyOwner == nullptr)
		return;

	AController* MyOwnerInstigator = MyOwner->GetInstigatorController();

	UClass* DamageTypeClass = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		UGameplayStatics::ApplyDamage(OtherActor, 50, MyOwnerInstigator, this, DamageTypeClass);
		Destroy();
	}

	//UE_LOG(LogTemp,Display, TEXT("HitComp: %s | OtherComp: %s"), *HitComp->GetName(),*OtherComp->GetName());
	//UE_LOG(LogTemp, Display, TEXT("Actor: %s"), *OtherActor->GetName());
	if(HitParticles)
	UGameplayStatics::SpawnEmitterAtLocation(this, HitParticles, GetActorLocation(), GetActorRotation());
	if(HitSound)
		UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());

}

