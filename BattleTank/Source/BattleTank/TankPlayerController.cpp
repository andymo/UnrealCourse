// Fill out your copyright notice in the Description page of Project Settings.
#include "TankPlayerController.h"
#include "TankAimingComponent.h"

#include "Engine/World.h"


ATankPlayerController::ATankPlayerController()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryActorTick.bCanEverTick = true;
}


void ATankPlayerController::BeginPlay() {
    Super::BeginPlay();

    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (ensure(AimingComponent))
        FoundAimingComponent(AimingComponent);
    else
        UE_LOG(LogTemp, Warning, TEXT("TANK PC: NO AIMING COMPONENT"))
}


void ATankPlayerController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    AimTowardsCrosshair();
}


void ATankPlayerController::AimTowardsCrosshair() {
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (!ensure(AimingComponent)) return;

    FVector HitLocation;
    if (GetSightRayHitLocation(HitLocation)) {
        AimingComponent->AimAt(HitLocation);
    } else {
        //UE_LOG(LogTemp, Warning, TEXT("Nothing found"));
    }
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const {
    // Find crosshair
    int32 ViewportSizeX, ViewportSizeY;
    FVector CameraLocation, LookDirection;

    GetViewportSize(ViewportSizeX, ViewportSizeY);
    FVector2D ScreenLocation = FVector2D(CrosshairXLocation * ViewportSizeX, CrosshairYLocation * ViewportSizeY);

    // Deproject screen position of crosshair to world direction
    if (!DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraLocation, LookDirection)) return false;

    // raytrace along direction up to some max range
    if (!GetLookDirectionHitLocation(CameraLocation, LookDirection, HitLocation)) return false;

    return true;
}


bool ATankPlayerController::GetLookDirectionHitLocation(FVector CameraLocation, FVector LookDirection, FVector& HitLocation) const {
    FHitResult HitResult;

    if (GetWorld()->LineTraceSingleByChannel(
        HitResult,
        CameraLocation,
        CameraLocation + LookDirection * LineTraceRangeKM * 100000,
        ECollisionChannel::ECC_Visibility,
        FCollisionQueryParams(FName(TEXT("")), false, GetOwner()),
        FCollisionResponseParams()
    )) {
        HitLocation = HitResult.Location;
        return true;
    } else {
        HitLocation = FVector(0.0f);
        return false;
    }
}
