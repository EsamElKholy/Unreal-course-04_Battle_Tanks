// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

UTankTrack::UTankTrack() 
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	// ...	
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	
}

void UTankTrack::OnHit(UPrimitiveComponent *hitComponent, AActor *otherActor, UPrimitiveComponent *otherComponent, FVector normalImpulse, const FHitResult &hit) 
{
	DriveTrack();
	ApplySidewaysForce();
	CurrentThrottle = 0;
}

void UTankTrack::ApplySidewaysForce()
{
	float slippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	auto deltaTime = GetWorld()->DeltaTimeSeconds;

	auto correctionAcceleration = -slippageSpeed / deltaTime * GetRightVector();

	auto tankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto correctionForce = (tankRoot->GetMass() * correctionAcceleration) / 2.0f;

	tankRoot->AddForce(correctionForce);
}

void UTankTrack::SetThrottle(float throttle)
{
	CurrentThrottle = FMath::Clamp(CurrentThrottle + throttle, -1.0f, 1.0f);
}

void UTankTrack::DriveTrack()
{
	auto forceApplied = CurrentThrottle * TrackMaxDrivingForce * GetForwardVector();
	auto forceLocation = GetComponentLocation();
	auto tankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());

	tankRoot->AddForceAtLocation(forceApplied, forceLocation);
}