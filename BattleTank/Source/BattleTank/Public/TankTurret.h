// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), hidecategories=(Collision) )
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
    void Turn(float RelativeSpeed);

private:
    UPROPERTY(EditAnywhere, Category=Setup)
    float MaxDegreesPerSecond = 5.0f;	
};
