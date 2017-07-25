// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankAimingComponent.generated.h"

// Enum state enum
UENUM()
enum class EFiringState : uint8 {
    Reloading,
    Aiming,
    Locked
};

class UTankBarrel;
class UTankTurret;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

    UFUNCTION(BlueprintCallable, Category="Setup")
    void Initialise(UTankBarrel* Barrel, UTankTurret* Turret);

    UTankBarrel* GetBarrel() const;
    void AimAt(FVector HitLocation, float LaunchSpeed);

protected:
    UPROPERTY(BlueprintReadOnly, Category="State")
    EFiringState FiringState = EFiringState::Reloading;

private:
    UTankBarrel* BarrelComponent = nullptr;
    UTankTurret* TurretComponent = nullptr;
    void MoveBarrel(FVector AimDirection);
	void MoveTurret(FVector AimDirection);
};
