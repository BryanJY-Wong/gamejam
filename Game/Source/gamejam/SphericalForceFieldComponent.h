// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "SphericalForceFieldComponent.generated.h"

UENUM()
enum class EDirection : uint8
{
	Inward,
	Outward
};

UCLASS()
class GAMEJAM_API USphericalForceFieldComponent : public USphereComponent
{
    GENERATED_BODY()
public:
	void ApplyForce();

	USphericalForceFieldComponent();

protected:
	UPROPERTY(EditInstanceOnly, Category = "Settings")
	float ForceMultiplier = 1.f;

	UPROPERTY(EditInstanceOnly, Category = "Settings")
	EDirection ForceDirection = EDirection::Inward;

	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	float ForceConstant = 4e9f;

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	float CalculateForceStrength(float DistanceSquared, float OtherMass) const;
};
