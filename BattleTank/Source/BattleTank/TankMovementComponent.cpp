// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::Initialize(UTankTrack * left, UTankTrack * right)
{RightTrack = right;
	LeftTrack = left;
}

void UTankMovementComponent::IntendMoveForward(float _throw)
{
	if (!LeftTrack || !RightTrack)
	{
		return;
	}

	LeftTrack->SetThrottle(_throw);
	RightTrack->SetThrottle(_throw);
}

void UTankMovementComponent::IntendTurnRight(float _throw)
{
	if (!LeftTrack || !RightTrack)
	{
		return;
	}

	LeftTrack->SetThrottle(_throw);
	RightTrack->SetThrottle(-_throw);
}