// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::IntendMoveForward(float _throw)
{
	LeftTrack->SetThrottle(_throw);
	RightTrack->SetThrottle(_throw);
}

void UTankMovementComponent::Initialize(UTankTrack * left, UTankTrack * right)
{
	if (!left || !right)
	{
		return;
	}

	RightTrack = right;
	LeftTrack = left;
}
