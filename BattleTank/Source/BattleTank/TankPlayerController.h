// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // It has to be the last thing to include

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

private:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:
	ATank* GetControlledTank() const;	
	
	void AimTowardsCrosshair();

	bool GetSightRayHiyLocation(FVector &hitLocation) const;
	bool GetLookDirection(FVector2D &screenLocation, FVector &worldDirection) const;
	bool GetLookVectorHitLocation(FVector &lookDirection, FVector &hitLocation) const;

private:
	UPROPERTY(EditAnywhere)
	float CrosshairXPosition = 0.5f;
	
	UPROPERTY(EditAnywhere)
	float CrosshairYPosition = 0.33333f;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000.0f;
};
