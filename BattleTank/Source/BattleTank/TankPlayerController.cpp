// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay() {
    Super::BeginPlay();

    ATank* ControlledTank = GetControlledTank();

    if (ControlledTank) {
        UE_LOG(LogTemp, Warning, TEXT("PlayerController:: BeginPlay: %s"), *ControlledTank->GetName());
    } else {
        UE_LOG(LogTemp, Warning, TEXT("FFFF NOTHING!!!!"));
    }
}



ATank* ATankPlayerController::GetControlledTank() const {
    return Cast<ATank>(GetPawn());
}
