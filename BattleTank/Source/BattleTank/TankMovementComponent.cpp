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

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	auto tankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwardIntention = MoveVelocity.GetSafeNormal();

	float angle = FVector::DotProduct(tankForward, AIForwardIntention);
	float right = FVector::CrossProduct(tankForward, AIForwardIntention).Z;

	IntendMoveForward(angle);
	IntendTurnRight(right);
}
