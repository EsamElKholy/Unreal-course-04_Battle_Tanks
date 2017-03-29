// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"

void UTankBarrel::Elevate(float relativeSpeed)
{
	auto clampedRelativeSpeed = FMath::Clamp(relativeSpeed, -1.0f, 1.0f);
	auto elevationChange = clampedRelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto rawElevation = RelativeRotation.Pitch + elevationChange;

	auto clampedElevation = FMath::Clamp(rawElevation, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation(FRotator(clampedElevation, 0, 0));
}