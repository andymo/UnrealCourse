// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * Responsible for Tank Movement
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category=Setup)
    void Initialise(UTankTrack* Left, UTankTrack* Right);
    UFUNCTION(BlueprintCallable, Category=Input)
    void IntendMoveForward(float Throw);
    UFUNCTION(BlueprintCallable, Category=Input)
    void IntendTurnRight(float Throw);

private:
    UTankTrack* LTankTrack = nullptr;
    UTankTrack* RTankTrack = nullptr;
};
