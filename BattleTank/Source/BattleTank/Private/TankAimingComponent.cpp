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
    if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeSeconds) {
        FiringState = EFiringState::Reloading;
    } else if (IsBarrelMoving()) {
        FiringState = EFiringState::Aiming;
    } else {
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
    AimDirection = LaunchVelocity.GetSafeNormal();

    MoveBarrel();
    MoveTurret();
}


void UTankAimingComponent::MoveBarrel() {
    if (!ensure(BarrelComponent)) return;

    FRotator CurrentRotation = BarrelComponent->GetForwardVector().Rotation();
    FRotator DeltaRotator = AimDirection.Rotation() - CurrentRotation;

    BarrelComponent->Elevate(DeltaRotator.Pitch);
}


bool UTankAimingComponent::IsBarrelMoving() {
    if (!ensure(BarrelComponent)) return false;
    auto BarrelForward = BarrelComponent->GetForwardVector();

    return !FVector2D(BarrelForward).Equals(FVector2D(AimDirection), 0.01f); 
}


void UTankAimingComponent::MoveTurret() {
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
}
