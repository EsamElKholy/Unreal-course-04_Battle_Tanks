// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};

class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
		
public:
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(UTankBarrel *barrel, UTankTurret *turret);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

	void AimAt(FVector hitLocation);

	EFiringState GetFiringState();

	UFUNCTION(BlueprintCallable, Category = Firing)
	int GetRoundsLeft() const;

private:
	void MoveBarrel(FVector aimDirection);
	bool IsBarrelMoving();

private:
	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 80000.0f;

	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditAnywhere, Category = Firing)
	float FireCoolDown = 3;

	double LastFireTime = 0;

	UTankBarrel *Barrel = nullptr;
	UTankTurret *Turret = nullptr;

	FVector AimDirection = FVector(0);

	int RoundsLeft = 3;

protected:
	UPROPERTY(BlueprintReadOnly, Category = State)
	EFiringState FiringState = EFiringState::Reloading;
};
