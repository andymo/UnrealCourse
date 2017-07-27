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
class AProjectile;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

    UFUNCTION(BlueprintCallable, Category="Setup")
    void Initialise(UTankBarrel* Barrel, UTankTurret* Turret);
    UFUNCTION(BlueprintCallable, Category="Firing")
    void Fire();

    void AimAt(FVector HitLocation);

protected:
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

    UPROPERTY(BlueprintReadOnly, Category="State")
    EFiringState FiringState = EFiringState::Reloading;

private:
    UTankBarrel* BarrelComponent = nullptr;
    UTankTurret* TurretComponent = nullptr;
    void MoveBarrel(FVector AimDirection);
	void MoveTurret(FVector AimDirection);

    UPROPERTY(EditDefaultsOnly, Category="Firing")
    float LaunchSpeed = 4000;
    UPROPERTY(EditAnywhere, Category="Firing")
    float ReloadTimeSeconds = 3.0f;
    UPROPERTY(EditDefaultsOnly, Category="Setup")
    TSubclassOf<AProjectile> ProjectileBlueprint;

    double LastFireTime = -ReloadTimeSeconds;
};
