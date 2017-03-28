// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"

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
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector hitLocation, float launchSpeed)
{
	if (!Barrel)
	{
		return;
	}

	FVector launchVelocity;
	FVector startLocation = Barrel->GetSocketLocation(FName("Projectile"));

	//..
	if (UGameplayStatics::SuggestProjectileVelocity
			(
				this,
				launchVelocity,
				startLocation,
				hitLocation,
				launchSpeed,
				false,
				0,
				0,
				ESuggestProjVelocityTraceOption::Type::DoNotTrace
			)
		)
	{
		FVector aimDirection = launchVelocity.SafeNormal();
		MoveBarrel(aimDirection);
	}		

	/*auto ourTankName = GetOwner()->GetName();
	auto barrelLocation = Barrel->GetComponentLocation().ToString();

	UE_LOG(LogTemp, Warning, TEXT("%s aiming at: %s , from: %s"), *ourTankName, *hitLocation.ToString(), *barrelLocation);*/
}

void UTankAimingComponent::SetBarrel(UTankBarrel *barrel)
{
	Barrel = barrel;
}

void UTankAimingComponent::MoveBarrel(FVector aimDirection)
{
	auto barrelRotator = Barrel->GetForwardVector().Rotation();
	auto aimRotator = aimDirection.Rotation();
	auto deltaRotator = aimRotator - barrelRotator;

	Barrel->Elevate(5);
}
