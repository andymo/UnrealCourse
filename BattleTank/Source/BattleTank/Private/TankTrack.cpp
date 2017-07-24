// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


void UTankTrack::SetThrottle(float Throttle) {
    auto ForceApplied = GetForwardVector() * Throttle * MaxTrackDriveForce;
    auto ForceLocation = GetComponentLocation();

    // cast because UPC allows force applied
    auto Tank = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    Tank->AddForceAtLocation(ForceApplied, ForceLocation);
}

