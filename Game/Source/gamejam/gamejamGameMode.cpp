// Copyright (c) Improbable Worlds Ltd, All Rights Reserved

#include "gamejamGameMode.h"
#include "UObject/ConstructorHelpers.h"

AgamejamGameMode::AgamejamGameMode()
{
	// Set default pawn class to our Blueprint character.
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/VehicleVarietyPack/Blueprints/SportsCar/BP_SportsCar"));
	static ConstructorHelpers::FClassFinder<APawn> SimulatedPawnBPClass(TEXT("/Game/StarterProject/Characters/SimulatedPlayers/SimulatedPlayerCharacter_BP"));

	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	if (SimulatedPawnBPClass.Class != NULL)
	{
		SimulatedPawnClass = SimulatedPawnBPClass.Class;
	}

	// Seamless Travel is not currently supported in SpatialOS [UNR-897]
	bUseSeamlessTravel = false;
}
