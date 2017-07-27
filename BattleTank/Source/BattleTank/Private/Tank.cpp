// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
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


void ATank::Fire() {
    return;

    double CurrentTime = FPlatformTime::Seconds();
    bool Ready = (CurrentTime - LastFireTime) > ReloadTimeSeconds;

    //UTankBarrel* BarrelComponent = TankAimingComponent->GetBarrel();
    UTankBarrel* BarrelComponent = nullptr;
    if (!ensure(BarrelComponent && Ready)) return;

    AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
        ProjectileBlueprint,
        BarrelComponent->GetSocketLocation(FName("LaunchLocation")),
        BarrelComponent->GetSocketRotation(FName("LaunchLocation"))
    );

    Projectile->Launch(LaunchSpeed);

    LastFireTime = CurrentTime;
}

