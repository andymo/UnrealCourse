// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankAimingComponent.generated.h"


class UTankBarrel;
class UTankTurret;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

    void SetBarrelReference(UTankBarrel* BarrelToSet);
    void SetTurretReference(UTankTurret* TurretToSet);
    void AimAt(FVector HitLocation, float LaunchSpeed);

private:
    UTankBarrel* BarrelComponent = nullptr;
    UTankTurret* TurretComponent = nullptr;
    void MoveBarrel(FVector AimDirection);
	void MoveTurret(FVector AimDirection);
};
