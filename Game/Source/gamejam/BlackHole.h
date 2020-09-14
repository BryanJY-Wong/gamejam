// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlackHole.generated.h"

class USphereComponent;
class UStaticMeshComponent;
class USphericalForceFieldComponent;


UCLASS()
class GAMEJAM_API ABlackHole : public AActor
{
	GENERATED_BODY()

	public:
	ABlackHole();

	UFUNCTION()
    void OnCollide(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	protected:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent* CollidableSphere;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphericalForceFieldComponent* SphericalForceField;

	virtual void BeginPlay() override;

};
