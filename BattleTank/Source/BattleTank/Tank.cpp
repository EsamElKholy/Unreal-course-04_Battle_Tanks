// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay() 
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
}

float ATank::TakeDamage(float damageAmount, FDamageEvent const & damageEvent, AController * eventInstigator, AActor * damageCauser)
{
	int32 damagePoints = FPlatformMath::RoundToInt(damageAmount);
	int32 damageTaken = FMath::Clamp(damagePoints, 0, CurrentHealth);
	
	CurrentHealth -= damageTaken;

	if (CurrentHealth <= 0)
	{
		CurrentHealth = 0;
		OnDeath.Broadcast();
	}

	return damageTaken;
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)MaxHealth;
}
