#include "PickUP.h"
#include "Net/UnrealNetwork.h"
#include "Components/SphereComponent.h" 

APickUP::APickUP()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	OverlapSphere = CreateDefaultSubobject<USphereComponent>(TEXT("OverlapSphere"));
	RootComponent = OverlapSphere;
	OverlapSphere->InitSphereRadius(100.f); 
	OverlapSphere->SetCollisionProfileName(TEXT("Trigger")); 
}

void APickUP::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		UE_LOG(LogTemp, Warning, TEXT("PickUP is available on the server."));

		OverlapSphere->OnComponentBeginOverlap.AddDynamic(this, &APickUP::OnOverlapBegin);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PickUP is available on the client."));
	}
}

void APickUP::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APickUP::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APickUP, bIsAvailable);
}

void APickUP::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this && HasAuthority())
	{
		BP_OnPickedUp(OtherActor);
	}
}