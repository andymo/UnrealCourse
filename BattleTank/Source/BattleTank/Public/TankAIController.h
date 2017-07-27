// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"


class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
    ATankAIController();
  
    virtual void BeginPlay() override;

private:
    virtual void Tick(float DeltaTime) override;
    void AimTowardsPlayer();

    float PlayerFindAcceptanceRadius = 3000.0f;

    APawn* PlayerTank;

    UTankAimingComponent* AimingComponent = nullptr;
};
