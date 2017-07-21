// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"

#include "Kismet/GameplayStatics.h"
#include "Components/ActorComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {
    if (!BarrelComponent) {
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
    if (!BarrelComponent) return;

    FRotator CurrentRotation = BarrelComponent->GetForwardVector().Rotation();
    FRotator DeltaRotator = AimDirection.Rotation() - CurrentRotation;

    BarrelComponent->Elevate(DeltaRotator.Pitch);
}


void UTankAimingComponent::MoveTurret(FVector AimDirection) {
    if (!TurretComponent) return;

    FRotator CurrentRotation = TurretComponent->GetForwardVector().Rotation();
    FRotator DeltaRotator = AimDirection.Rotation() - CurrentRotation;

    TurretComponent->Turn(DeltaRotator.Yaw);
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) {
    BarrelComponent = BarrelToSet;
}


void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet) {
    TurretComponent = TurretToSet;
}

