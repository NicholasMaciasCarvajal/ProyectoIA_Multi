#include "AI/CustomAIController.h"
#include "GameplayStateTreeModule/Public/Components/StateTreeAIComponent.h"


ACustomAIController::ACustomAIController()
{
	StateTreeComponent = CreateDefaultSubobject<UStateTreeAIComponent>(TEXT("StateTreeComponent"));
	check(StateTreeComponent);
}

void ACustomAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// Asegura que la lógica arranque en cuanto el AIController posee al CharacterIA
	if (StateTreeComponent)
	{
		StateTreeComponent->StartLogic();
	}
}