// Copyright Epic Games, Inc. All Rights Reserved.

//#include "Online/ProyectoIA_MultiGameMode.h"
#include "ProyectoIA_MultiGameMode.h"

AProyectoIA_MultiGameMode::AProyectoIA_MultiGameMode()
{
	// stub
}

void AProyectoIA_MultiGameMode::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("GAMEMODE"));
}