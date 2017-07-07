// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    FVector Location;
    FRotator Rotation;
	// Get player viewpoint
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(Location, Rotation);

    //UE_LOG(LogTemp, Warning, TEXT("Position: %s, Rotation: %s"), *(Location.ToString()), *(Rotation.ToString()))

    // draw a red debug line
    FVector LineTraceEnd = Location + Rotation.Vector() * Reach;
    UKismetSystemLibrary::DrawDebugLine(GetWorld(), Location, LineTraceEnd, FColor(255, 0, 0), 0.f, 10.f);

    // raycast out distance
    FHitResult TraceHit;
    FCollisionQueryParams TraceParams = FCollisionQueryParams(FName(TEXT("")), false, GetOwner());
    if (GetWorld()->LineTraceSingleByObjectType(
            TraceHit,
            Location,
            LineTraceEnd,
            FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
            TraceParams)) {
        UE_LOG(LogTemp, Warning, TEXT("HOLY SHIT WE HIT %s"), *(TraceHit.GetActor()->GetName()))
    }

    // see what we hit
}

