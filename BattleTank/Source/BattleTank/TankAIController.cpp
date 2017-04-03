// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"
#include "TankAimingComponent.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsPlayer();

	auto playerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (ensure(playerTank))
	{
		MoveToActor(playerTank, AcceptanceRadius);
	}
}

void ATankAIController::SetPawn(APawn * inPawn)
{
	Super::SetPawn(inPawn);

	if (inPawn)
	{
		auto possessedTank = Cast<ATank>(inPawn);

		if (!ensure(possessedTank))
		{
			return;
		}

		//..
		possessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnPossessedTankDeath);
	}
}

void ATankAIController::OnPossessedTankDeath()
{
	if (!GetPawn())
	{
		return;
	}

	GetPawn()->DetachFromControllerPendingDestroy();
}

void ATankAIController::AimTowardsPlayer()
{
	auto controlledTank = GetPawn();
	auto playerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	if (!ensure(playerTank && controlledTank))
	{
		return;
	}

	auto aimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	aimingComponent->AimAt(playerTank->GetActorLocation());

	if (aimingComponent->GetFiringState() == EFiringState::Locked)
	{
		aimingComponent->Fire();
	}
}

