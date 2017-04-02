// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankPlayerController.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay() 
{
	Super::BeginPlay();

	auto controlledTank = GetControlledTank();

	if (!ensure(controlledTank))
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't find player tank"));
	}
	else
	{
		auto aimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();

		if (aimingComponent)
		{
			FoundTankAimingComponent(aimingComponent);
		}
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const 
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!ensure(GetControlledTank()))
	{
		return;
	}

	//..
	FVector hitLocation;

	if (GetSightRayHiyLocation(hitLocation)) 
	{
		//..
		GetControlledTank()->AimAt(hitLocation);
	}
}

bool ATankPlayerController::GetSightRayHiyLocation(FVector & hitLocation) const
{
	int32 viewportSizeX, viewportSizeY;

	GetViewportSize(viewportSizeX, viewportSizeY);

	FVector2D screenLocation = FVector2D(viewportSizeX * CrosshairXPosition, viewportSizeY * CrosshairYPosition);

	FVector worldDirection;

	if (GetLookDirection(screenLocation, worldDirection))
	{
		//..
		GetLookVectorHitLocation(worldDirection, hitLocation);
	}

	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D screenLocation, FVector &worldDirection) const
{
	FVector camLoc;
	return DeprojectScreenPositionToWorld(screenLocation.X, screenLocation.Y, camLoc, worldDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector lookDirection, FVector & hitLocation) const
{
	FHitResult hitResult;
	
	FVector startLocation = PlayerCameraManager->GetCameraLocation();
	FVector endLocation = startLocation + (lookDirection * LineTraceRange);

	if (GetWorld()->
		LineTraceSingleByChannel(
								hitResult,
								startLocation,
								endLocation,
								ECollisionChannel::ECC_Visibility
								)
		)
	{
		hitLocation = hitResult.Location;

		return true;
	}

	hitLocation = FVector(0.0f);

	return false;
}




