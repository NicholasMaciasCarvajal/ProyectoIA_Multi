// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "CharacterIA.generated.h"

UCLASS()
class PROYECTOIA_MULTI_API ACharacterIA : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACharacterIA();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<class UFloatingPawnMovement> Movement;

	// State tree component used to send events to the StateTree
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "IA")
	// TObjectPtr<class UStateTreeComponent> StateTreeComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
