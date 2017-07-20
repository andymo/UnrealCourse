// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UTankAimingComponent::AimAt(FVector HitLocation) {
    if (BarrelComponent) {
        UE_LOG(LogTemp, Warning, TEXT("%s Aiming at: %s; From: %s"),
               *GetOwner()->GetName(),
               *HitLocation.ToString(),
               *BarrelComponent->GetComponentLocation().ToString());
    } else {
        UE_LOG(LogTemp, Warning, TEXT("%s has no barrel"), *GetOwner()->GetName());
    }
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent* BarrelToSet) {
    BarrelComponent = BarrelToSet;
}

