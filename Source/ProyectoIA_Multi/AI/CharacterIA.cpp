// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/CharacterIA.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "CustomAIController.h"
#include "Components/StateTreeComponent.h"

// Sets default values
ACharacterIA::ACharacterIA()
{
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	// StateTreeComponent = CreateDefaultSubobject<UStateTreeComponent>(TEXT("StateTreeComponent"));
	AIControllerClass = ACustomAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACharacterIA::BeginPlay()
{
	Super::BeginPlay();
	// StateTreeComponent->SendStateTreeEvent(FGameplayTag::RequestGameplayTag("IA.EnemigoDetectado"));
}

// Called every frame
void ACharacterIA::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterIA::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
