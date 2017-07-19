// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
    ATankPlayerController();
    ATank* GetControlledTank() const;
	
protected:
	virtual void BeginPlay() override;

private:
    virtual void Tick(float DeltaTime) override;

    void AimTowardsCrosshair();
    bool GetSightRayHitLocation(FVector& HitLocation) const;

    ATank* ControlledTank;
};
