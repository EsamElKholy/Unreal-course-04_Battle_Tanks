// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::Initialize(UTankBarrel * barrel, UTankTurret * turret)
{
	Barrel = barrel;
	Turret = turret;
}

void UTankAimingComponent::AimAt(FVector hitLocation, float launchSpeed)
{
	if (!ensure(Barrel))
	{
		return;
	}

	FVector launchVelocity;
	FVector startLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool hasSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		launchVelocity,
		startLocation,
		hitLocation,
		launchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	//..
	if (hasSolution)
	{
		FVector aimDirection = launchVelocity.GetSafeNormal();
		MoveBarrel(aimDirection);
	}	
}

void UTankAimingComponent::MoveBarrel(FVector aimDirection)
{
	if (!ensure(Turret && Barrel))
	{
		return;
	}

	auto barrelRotator = Barrel->GetForwardVector().Rotation();
	auto aimRotator = aimDirection.Rotation();
	auto deltaRotator = aimRotator - barrelRotator;

	Barrel->Elevate(deltaRotator.Pitch);
	Turret->RotateHorizontally(deltaRotator.Yaw);
}
