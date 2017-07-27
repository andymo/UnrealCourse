// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

#include "Kismet/GameplayStatics.h"
#include "Components/ActorComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay() {
    Super::BeginPlay();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) {
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    if ((FPlatformTime::Seconds() - LastFireTime) > ReloadTimeSeconds) {
        FiringState = EFiringState::Locked;
    }
}


void UTankAimingComponent::Initialise(UTankBarrel* Barrel, UTankTurret* Turret) {
    BarrelComponent = Barrel;
    TurretComponent = Turret;
}


void UTankAimingComponent::AimAt(FVector HitLocation) {
    if (!ensure(BarrelComponent)) {
        UE_LOG(LogTemp, Warning, TEXT("%s has no barrel"), *GetOwner()->GetName());
        return;
    }

    FVector LaunchVelocity;
    FVector StartLocation = BarrelComponent->GetSocketLocation(FName("LaunchLocation"));

    if (!UGameplayStatics::SuggestProjectileVelocity(
            this,
            LaunchVelocity,
            StartLocation,
            HitLocation,
            LaunchSpeed,
            false,
            0.0f,
            0.0f,
            ESuggestProjVelocityTraceOption::DoNotTrace)) {
        return;
    }
    FVector AimDirection = LaunchVelocity.GetSafeNormal();

    MoveBarrel(AimDirection);
    MoveTurret(AimDirection);
}


void UTankAimingComponent::MoveBarrel(FVector AimDirection) {
    if (!ensure(BarrelComponent)) return;

    FRotator CurrentRotation = BarrelComponent->GetForwardVector().Rotation();
    FRotator DeltaRotator = AimDirection.Rotation() - CurrentRotation;

    BarrelComponent->Elevate(DeltaRotator.Pitch);
}


void UTankAimingComponent::MoveTurret(FVector AimDirection) {
    if (!ensure(TurretComponent)) return;

    FRotator CurrentRotation = TurretComponent->GetForwardVector().Rotation();
    FRotator DeltaRotator = AimDirection.Rotation() - CurrentRotation;

    TurretComponent->Turn(DeltaRotator.Yaw);
}


void UTankAimingComponent::Fire() {
    if (!ensure(BarrelComponent && ProjectileBlueprint)) return;
    if (FiringState == EFiringState::Reloading) return;

    AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
        ProjectileBlueprint,
        BarrelComponent->GetSocketLocation(FName("LaunchLocation")),
        BarrelComponent->GetSocketRotation(FName("LaunchLocation"))
    );
    Projectile->Launch(LaunchSpeed);

    LastFireTime = FPlatformTime::Seconds();
    FiringState = EFiringState::Reloading;
}
