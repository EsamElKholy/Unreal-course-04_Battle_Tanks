// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	auto controlledTank = GetControlledTank();
	auto playerTank = GetPlayerTank();

	if (!controlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't find AI tank"));
	}
	else
	{
		if (!playerTank)
		{
			UE_LOG(LogTemp, Warning, TEXT("AI tank ( %s ) couldn't findd player tank"), *(controlledTank->GetName()));
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("AI tank ( %s ) found player tank ( %s )"), *(controlledTank->GetName()), *(playerTank->GetName()));
		}
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsPlayer();
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

void ATankAIController::AimTowardsPlayer()
{
	auto controlledTank = GetControlledTank();
	auto playerTank = GetPlayerTank();

	if (!playerTank || !controlledTank)
	{
		return;
	}

	controlledTank->AimAt(playerTank->GetActorLocation());
}
