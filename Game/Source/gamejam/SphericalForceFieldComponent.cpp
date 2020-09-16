#include "SphericalForceFieldComponent.h"

USphericalForceFieldComponent::USphericalForceFieldComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void USphericalForceFieldComponent::BeginPlay()
{
    Super::BeginPlay();
    SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Overlap);
}

float USphericalForceFieldComponent::CalculateForceStrength(float DistanceSquared, float OtherMass) const
{
    float InvDistanceSquared = 1.f / DistanceSquared;
    float Sign = (ForceDirection == EDirection::Inward) ? -1 : 1;
    return Sign * ForceConstant * ForceMultiplier * OtherMass * InvDistanceSquared;
}

void USphericalForceFieldComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    ApplyForce();
}

void USphericalForceFieldComponent::ApplyForce()
{
    AActor* Owner = GetOwner();
    if (Owner == nullptr)
    {
        return;
    }

    TSet<UPrimitiveComponent*> IntersectingComponents;
    GetOverlappingComponents(IntersectingComponents);

    for (UPrimitiveComponent* OtherComp : IntersectingComponents)
    {
        if (OtherComp == nullptr || !OtherComp->IsSimulatingPhysics())
        {
            continue;
        }

        AActor* OtherActor = OtherComp->GetOwner();
        if (OtherActor == nullptr || OtherActor == Owner)
        {
            continue;
        }

        float DistanceSquared = Owner->GetSquaredDistanceTo(OtherActor);
        float Strength = CalculateForceStrength(DistanceSquared, OtherComp->GetMass());
        OtherComp->AddRadialForce(Owner->GetActorLocation(), DistanceSquared, Strength, ERadialImpulseFalloff::RIF_Constant);
    }
}
