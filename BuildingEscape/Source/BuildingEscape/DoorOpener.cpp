// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorOpener.h"


// Sets default values for this component's properties
UDoorOpener::UDoorOpener()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorOpener::BeginPlay()
{
    Super::BeginPlay();

    ThisComponent = GetOwner();
}


// Called every frame
void UDoorOpener::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetPlateMass() >= TriggerMass) {
        OnOpen.Broadcast();
    } else {
        OnClose.Broadcast();
    }
}


float UDoorOpener::GetPlateMass() {
    if (PressurePlate == nullptr) {
        return 0;
    }

    float TotalMass = 0;
    TArray<AActor*> ActorsOnPlate;

    PressurePlate->GetOverlappingActors(ActorsOnPlate);

    for (auto* Actor : ActorsOnPlate) {
        TotalMass +=  Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();  
    }
    return TotalMass;
}
