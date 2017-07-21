// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"


void UTankBarrel::Elevate(float RelativeSpeed) {
    RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.0f, 1.0f);

    float ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;

    float NewElevation = FMath::Clamp(RelativeRotation.Pitch + ElevationChange, MinElevationDegrees, MaxElevationDegrees);
    SetRelativeRotation(FRotator(NewElevation, 0, 0));
}

