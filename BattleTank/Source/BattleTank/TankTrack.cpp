// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

void UTankTrack::SetThrottle(float throttle)
{
	auto forceApplied = throttle * TrackMaxDrivingForce * GetForwardVector();
	auto forceLocation = GetComponentLocation();
	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
}