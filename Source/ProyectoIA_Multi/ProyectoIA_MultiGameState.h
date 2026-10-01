// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ProyectoIA_MultiGameState.generated.h"

/**
 * 
 */
UCLASS()
class PROYECTOIA_MULTI_API AProyectoIA_MultiGameState : public AGameStateBase
{
	GENERATED_BODY()
	
	virtual void BeginPlay() override;

};
