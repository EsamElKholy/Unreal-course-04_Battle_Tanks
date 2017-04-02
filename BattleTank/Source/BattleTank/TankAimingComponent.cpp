// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...	
	LastFireTime = FPlatformTime::Seconds();
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	//Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if ((FPlatformTime::Seconds() - LastFireTime) < FireCoolDown)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}

bool UTankAimingComponent::IsBarrelMoving() 
{
	if (!ensure(Barrel))
	{
		return false;
	}

	return !(Barrel->GetForwardVector().Equals(AimDirection, 0.01f));
}

void UTankAimingComponent::Initialize(UTankBarrel * barrel, UTankTurret * turret)
{
	Barrel = barrel;
	Turret = turret;
}

void UTankAimingComponent::AimAt(FVector hitLocation)
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
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	//..
	if (hasSolution)
	{
		AimDirection = launchVelocity.GetSafeNormal();
		MoveBarrel(AimDirection);
	}	
}

EFiringState UTankAimingComponent::GetFiringState()
{
	return FiringState;
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

	if (FMath::Abs(deltaRotator.Yaw) < 180.0f)
	{
		Turret->RotateHorizontally(deltaRotator.Yaw);
	}
	else
	{
		Turret->RotateHorizontally(-deltaRotator.Yaw);
	}	
}

void UTankAimingComponent::Fire()
{
	if (FiringState != EFiringState::Reloading)
	{
		if (!ensure(Barrel ))
		{
			return;
		}

		if (!ensure(ProjectileBlueprint))
		{
			return;
		}

		auto projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation(FName("Projectile")), Barrel->GetSocketRotation(FName("Projectile")));
		projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}