// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackHole.h"
#include "SphericalForceFieldComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ABlackHole::ABlackHole()
{
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	CollidableSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollidableSphere"));
	SphericalForceField = CreateDefaultSubobject<USphericalForceFieldComponent>(TEXT("SphericalForceField"));
	SetRootComponent(StaticMesh);
	CollidableSphere->SetupAttachment(StaticMesh);
	SphericalForceField->SetupAttachment(StaticMesh);
}

void ABlackHole::OnCollide(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	bool bIsParametersNull = OverlappedComp == nullptr || OtherActor == nullptr || OtherComp == nullptr;
	if (bIsParametersNull || !OtherComp->IsSimulatingPhysics())
	{
		return;
	}
	OtherActor->Destroy();
}

void ABlackHole::BeginPlay()
{
	Super::BeginPlay();
	check(StaticMesh != nullptr);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	check(CollidableSphere != nullptr);
	CollidableSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollidableSphere->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	CollidableSphere->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Overlap);
	CollidableSphere->OnComponentBeginOverlap.AddDynamic(this, &ABlackHole::OnCollide);
}


