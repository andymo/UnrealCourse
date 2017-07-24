// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialise(UTankTrack* Left, UTankTrack* Right) {
    if (!Left || !Right) return;

    LTankTrack = Left;
    RTankTrack = Right;
}


void UTankMovementComponent::IntendMoveForward(float Throw) {
    UE_LOG(LogTemp, Warning, TEXT("Throw %f"), Throw);

    LTankTrack->SetThrottle(Throw);
    RTankTrack->SetThrottle(Throw);
}

