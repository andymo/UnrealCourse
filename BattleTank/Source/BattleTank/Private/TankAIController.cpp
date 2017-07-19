// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay() {
    Super::BeginPlay();

    ATank* ControlledTank = GetControlledTank();

    if (ControlledTank) {
        UE_LOG(LogTemp, Warning, TEXT("TankAIController:: BeginPlay: %s"), *ControlledTank->GetName());
    } else {
        UE_LOG(LogTemp, Warning, TEXT("FFFF NOTHING!!!!"));
    }

    ATank* PlayerTank = GetPlayerTank();
    if (PlayerTank) {
        UE_LOG(LogTemp, Warning, TEXT("TankAIController:: FoundPlayer: %s"), *PlayerTank->GetName());
    } else {
        UE_LOG(LogTemp, Warning, TEXT("DID NOT FIND PLAYER"));
    }
}



ATank* ATankAIController::GetControlledTank() const {
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const {
    auto PlayerTankController = GetWorld()->GetFirstPlayerController();

    if (!PlayerTankController)
        return nullptr;
    else
        return Cast<ATank>(PlayerTankController->GetPawn());
}