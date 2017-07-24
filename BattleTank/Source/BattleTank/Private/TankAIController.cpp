// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

ATankAIController::ATankAIController()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryActorTick.bCanEverTick = true;
}


void ATankAIController::BeginPlay() {
    Super::BeginPlay();

    ControlledTank = Cast<ATank>(GetPawn());
    if (ControlledTank) {
        UE_LOG(LogTemp, Warning, TEXT("TankAIController:: BeginPlay: %s"), *ControlledTank->GetName());
    } else {
        UE_LOG(LogTemp, Warning, TEXT("FFFF NOTHING!!!!"));
    }

    auto PlayerTankController = GetWorld()->GetFirstPlayerController();
    if (!PlayerTankController)
        PlayerTank =  nullptr;
    else
        PlayerTank = Cast<ATank>(PlayerTankController->GetPawn());

    if (PlayerTank) {
        UE_LOG(LogTemp, Warning, TEXT("TankAIController:: FoundPlayer: %s"), *PlayerTank->GetName());
    } else {
        UE_LOG(LogTemp, Warning, TEXT("DID NOT FIND PLAYER"));
    }
}


void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    MoveToActor(PlayerTank, PlayerFindAcceptanceRadius);
    AimTowardsPlayer();
    ControlledTank->Fire();
}


void ATankAIController::AimTowardsPlayer() {
    if (!ControlledTank || !PlayerTank) return;

    ControlledTank->AimAt(PlayerTank->GetActorLocation());
}
