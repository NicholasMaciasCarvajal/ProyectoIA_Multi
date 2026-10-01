#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CustomAIController.generated.h"

class UStateTreeComponent;

/**
 *
 */
UCLASS()
class PROYECTOIA_MULTI_API ACustomAIController : public AAIController
{
	GENERATED_BODY()
public:
	ACustomAIController();
private:
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "IA")
	TObjectPtr<UStateTreeComponent> StateTreeComponent;
};