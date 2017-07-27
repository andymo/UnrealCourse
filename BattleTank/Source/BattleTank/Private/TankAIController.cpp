// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"

ATankAIController::ATankAIController()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryActorTick.bCanEverTick = true;
}


void ATankAIController::BeginPlay() {
    Super::BeginPlay();

    AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (!ensure(AimingComponent))
        UE_LOG(LogTemp, Warning, TEXT("TANK AI: NO AIMING COMPONENT"))

    auto PlayerTankController = GetWorld()->GetFirstPlayerController();
    if (!ensure(PlayerTankController))
        PlayerTank =  nullptr;
    else
        PlayerTank = PlayerTankController->GetPawn();

    if (ensure(PlayerTank)) {
        UE_LOG(LogTemp, Warning, TEXT("TankAIController:: FoundPlayer: %s"), *PlayerTank->GetName());
    } else {
        UE_LOG(LogTemp, Warning, TEXT("DID NOT FIND PLAYER"));
    }
}


void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    if (!ensure(AimingComponent)) return;

    MoveToActor(PlayerTank, PlayerFindAcceptanceRadius);
    AimTowardsPlayer();
    //Cast<ATank>(GetPawn())->Fire();
}


void ATankAIController::AimTowardsPlayer() {
    if (!ensure(PlayerTank)) return;

    AimingComponent->AimAt(PlayerTank->GetActorLocation());
}
