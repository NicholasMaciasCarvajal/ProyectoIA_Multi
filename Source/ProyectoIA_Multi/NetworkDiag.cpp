// Fill out your copyright notice in the Description page of Project Settings.


#include "NetworkDiag.h"

// Sets default values for this component's properties
UNetworkDiag::UNetworkDiag()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UNetworkDiag::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UNetworkDiag::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UNetworkDiag::PrintNetworkRoles()
{
	AActor* Owner = GetOwner();

	if(Owner)
	{
		ENetMode NetMode = Owner->GetNetMode();
		ENetRole LocalRole = Owner->GetLocalRole();
		ENetRole RemoteRole = Owner->GetRemoteRole();

		FString NetModeString = (NetMode == NM_Client) ? TEXT("Client") : TEXT("Server");

	}
}

