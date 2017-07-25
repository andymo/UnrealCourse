// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"


class UTankAimingComponent;

class AProjectile;


UCLASS()
class BATTLETANK_API ATank : public APawn
{
    GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
    ATank();

    void AimAt(FVector HitLocation);
    UFUNCTION(BlueprintCallable)
    void Fire();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UPROPERTY(BlueprintReadOnly)
    UTankAimingComponent* TankAimingComponent = nullptr;

private:
    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UPROPERTY(EditDefaultsOnly, Category="Setup")
    TSubclassOf<AProjectile> ProjectileBlueprint;

    UPROPERTY(EditDefaultsOnly, Category="Firing")
    float LaunchSpeed = 4000;
    UPROPERTY(EditAnywhere, Category="Firing")
    float ReloadTimeSeconds = 3.0f;

    double LastFireTime = -ReloadTimeSeconds;
};
