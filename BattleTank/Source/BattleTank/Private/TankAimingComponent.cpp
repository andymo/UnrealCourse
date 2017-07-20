// Fill out your copyright notice in the Description page of Project Settings.
#include "TankAimingComponent.h"
#include "TankBarrel.h"

#include "Kismet/GameplayStatics.h"
#include "Components/ActorComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

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
            ESuggestProjVelocityTraceOption::DoNotTrace)) {
        return;
    }
    FVector AimDirection = LaunchVelocity.GetSafeNormal();

    MoveBarrel(AimDirection);
}


void UTankAimingComponent::MoveBarrel(FVector AimDirection) {
    FRotator CurrentRotation = BarrelComponent->GetForwardVector().Rotation();
    FRotator AimRotation = AimDirection.Rotation();

    FRotator DeltaRotator = AimRotation - CurrentRotation;
    UE_LOG(LogTemp, Warning, TEXT("%s Aiming at: %s"),
           *GetOwner()->GetName(),
           *AimDirection.ToString());

    BarrelComponent->Elevate(5.0f);
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet) {
    BarrelComponent = BarrelToSet;
}

