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

    AActor* ThisComponent = GetOwner();
    FString Roto = ThisComponent->GetTransform().GetRotation().ToString();
    UE_LOG(LogTemp, Warning, TEXT("%s is rotated to (%s)"), *(ThisComponent->GetName()), *Roto);

    FRotator NewRotation = FRotator(0.0f, 60.0f, 0.0f);
    ThisComponent->SetActorRotation(NewRotation);
}


// Called every frame
void UDoorOpener::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

