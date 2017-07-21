// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"


void UTankTurret::Turn(float RelativeSpeed) {
    RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.0f, 1.0f);

    float YawChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    float NewYaw = RelativeRotation.Yaw + YawChange;
    SetRelativeRotation(FRotator(0, NewYaw, 0));
}

