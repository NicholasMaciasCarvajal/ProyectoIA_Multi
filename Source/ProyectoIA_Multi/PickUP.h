#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUP.generated.h"

class USphereComponent;

UCLASS()
class PROYECTOIA_MULTI_API APickUP : public AActor
{
	GENERATED_BODY()

public:
	APickUP();

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Replicated")
	bool bIsAvailable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* OverlapSphere;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintImplementableEvent, Category = "PickUp")
	void BP_OnPickedUp(AActor* ActorCollector);
};