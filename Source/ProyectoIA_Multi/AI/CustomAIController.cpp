#include "AI/CustomAIController.h"
#include "Components/StateTreeComponent.h" 

ACustomAIController::ACustomAIController()
{
	StateTreeComponent = CreateDefaultSubobject<UStateTreeComponent>(TEXT("StateTreeComponent"));
}