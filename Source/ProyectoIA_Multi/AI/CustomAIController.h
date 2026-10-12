#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CustomAIController.generated.h"

class UStateTreeAIComponent;

/**
 *
 */
UCLASS()
class PROYECTOIA_MULTI_API ACustomAIController : public AAIController
{
	GENERATED_BODY()
public:
	ACustomAIController();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "IA")
	FVector CoverLocation = FVector::ZeroVector;

private:
protected:
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "IA")
	TObjectPtr<UStateTreeAIComponent> StateTreeComponent;
};