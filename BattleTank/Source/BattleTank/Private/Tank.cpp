// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ATank::SetBarrelReference(UTankBarrel* Barrel) {
    TankAimingComponent->SetBarrelReference(Barrel);
    BarrelComponent = Barrel;
}


void ATank::SetTurretReference(UTankTurret* Turret) {
    TankAimingComponent->SetTurretReference(Turret);
}


void ATank::AimAt(FVector HitLocation) {
    TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}


void ATank::Fire() {
    double CurrentTime = FPlatformTime::Seconds();
    bool Ready = (CurrentTime - LastFireTime) > ReloadTimeSeconds;

    if (!BarrelComponent || !Ready) return;

    AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
        ProjectileBlueprint,
        BarrelComponent->GetSocketLocation(FName("LaunchLocation")),
        BarrelComponent->GetSocketRotation(FName("LaunchLocation"))
    );

    Projectile->Launch(LaunchSpeed);

    LastFireTime = CurrentTime;
}

