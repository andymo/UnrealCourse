// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialise(UTankTrack* Left, UTankTrack* Right) {
    LTankTrack = Left;
    RTankTrack = Right;
}


void UTankMovementComponent::IntendMoveForward(float Throw) {
    if (!LTankTrack || !RTankTrack) return;
    LTankTrack->SetThrottle(Throw);
    RTankTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw) {
    if (!LTankTrack || !RTankTrack) return;
    LTankTrack->SetThrottle(Throw);
    RTankTrack->SetThrottle(-Throw);
}
