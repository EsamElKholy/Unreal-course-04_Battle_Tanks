// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTurret.h"

void UTankTurret::RotateHorizontally(float relativeSpeed)
{
	auto clampedRelativeSpeed = FMath::Clamp(relativeSpeed, -1.0f, 1.0f);
	auto rotationChange = clampedRelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto rawRotation = RelativeRotation.Yaw + rotationChange;

	UE_LOG(LogTemp, Warning, TEXT("%f"), relativeSpeed);

	SetRelativeRotation(FRotator(0, rawRotation, 0));
}