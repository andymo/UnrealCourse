// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

ATankPlayerController::ATankPlayerController()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryActorTick.bCanEverTick = true;
}


void ATankPlayerController::BeginPlay() {
    Super::BeginPlay();

    ControlledTank = GetControlledTank();
    if (ControlledTank) {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController:: BeginPlay: %s"), *ControlledTank->GetName());
    } else {
        UE_LOG(LogTemp, Warning, TEXT("FFFF NOTHING!!!!"));
    }
}


void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    AimTowardsCrosshair();
}


ATank* ATankPlayerController::GetControlledTank() const {
    return Cast<ATank>(GetPawn());
}


void ATankPlayerController::AimTowardsCrosshair() {
    if (!ControlledTank) return;

    FVector HitLocation;
    if (GetSightRayHitLocation(HitLocation)) {
        UE_LOG(LogTemp, Warning, TEXT("FOUND SOMETHING AT %s"), *HitLocation.ToString());
        // TODO: aim at thing
    } else {
        UE_LOG(LogTemp, Warning, TEXT("Nothing found"));
    }
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const {
    HitLocation = FVector(1.0f);
    return true;
}
