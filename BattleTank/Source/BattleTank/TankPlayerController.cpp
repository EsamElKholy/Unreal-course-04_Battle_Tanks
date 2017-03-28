// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() 
{
	Super::BeginPlay();

	auto controlledTank = GetControlledTank();

	if (!controlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't find player tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Found player tank: %s"), *(controlledTank->GetName()));
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
	if (!GetControlledTank())
	{
		return;
	}

	//..
	FVector hitLocation;

	if (GetSightRayHiyLocation(hitLocation)) 
	{
		//..
	}
}

bool ATankPlayerController::GetSightRayHiyLocation(FVector & hitLocation) const
{
	int32 viewportSizeX, viewportSizeY;

	GetViewportSize(viewportSizeX, viewportSizeY);

	FVector2D screenLocation = FVector2D(viewportSizeX * CrosshairXPosition, viewportSizeY * CrosshairYPosition);

	return false;
}




