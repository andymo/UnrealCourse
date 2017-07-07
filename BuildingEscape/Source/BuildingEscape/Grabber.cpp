// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

    GetPhysicsHandle();
    SetupInputComponent();
}


void UGrabber::GetPhysicsHandle() {
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if (!PhysicsHandle) {
        UE_LOG(LogTemp, Error, TEXT("OH GOD OH MAN NO HANDLE ON %s"), *(GetOwner()->GetName()));
    }
}


void UGrabber::SetupInputComponent() {
    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if (!InputComponent) {
        UE_LOG(LogTemp, Error, TEXT("OH GOD OH MAN NO INPUT ON %s"), *(GetOwner()->GetName()));
    } else {
        InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
        InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
    }
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    if (PhysicsHandle && PhysicsHandle->GrabbedComponent) {
        PhysicsHandle->SetTargetLocation(GetReachLine()[1]);
    }
}


void UGrabber::Grab() {
    if (PhysicsHandle) {
        FHitResult HitResult = GetBodyInReach();

        if (HitResult.GetActor()) {
            auto ComponentToGrab = HitResult.GetComponent();
            PhysicsHandle->GrabComponent(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), true);
        }
    }
}


void UGrabber::Release() {
    if (PhysicsHandle) {
        PhysicsHandle->ReleaseComponent();
    }
}


const FHitResult UGrabber::GetBodyInReach() {
    // raycast out distance
    FHitResult TraceHit;
    FCollisionQueryParams TraceParams = FCollisionQueryParams(FName(TEXT("")), false, GetOwner());
    TArray<FVector> ReachLine = GetReachLine();

    if (GetWorld()->LineTraceSingleByObjectType(
            TraceHit,
            ReachLine[0],
            ReachLine[1],
            FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
            TraceParams)) {
        UE_LOG(LogTemp, Warning, TEXT("HOLY SHIT WE HIT %s"), *(TraceHit.GetActor()->GetName()))
    }

    return TraceHit;
}

TArray<FVector> UGrabber::GetReachLine() {
    FVector Location;
    FRotator Rotation;

    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(Location, Rotation);

    TArray<FVector> ReachLineArray = {Location, Location + Rotation.Vector() * Reach};
    return ReachLineArray;
}
