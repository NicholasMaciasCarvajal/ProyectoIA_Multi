#include "AI/StateTreeTask_FindCover.h"
#include "StateTreeExecutionContext.h"
#include "Components/StateTreeComponent.h"
#include "AIController.h"
#include "EnvironmentQuery/EnvQueryManager.h"

// 1. En el constructor, indicamos que esta tarea necesita ejecutar el método Tick
FStateTreeTask_FindCover::FStateTreeTask_FindCover()
{
    bShouldCallTick = true; // Fundamental para que el Tick se ejecute mientras está en estado Running
}

// (Tu destructor se queda igual)

EStateTreeRunStatus FStateTreeTask_FindCover::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
    FInstanceDataType& InstanceData = Context.GetInstanceData<FInstanceDataType>(*this);
    InstanceData.ExecutionStatus = EStateTreeRunStatus::Running;
    InstanceData.AIController = Cast<AAIController>(Context.GetOwner());

    if (!InstanceData.CoverQuery || !InstanceData.AIController)
    {
        return EStateTreeRunStatus::Failed;
    }

    APawn* ControlledPawn = InstanceData.AIController->GetPawn();
    if (!ControlledPawn)
    {
        return EStateTreeRunStatus::Failed;
    }

    // Inicializamos nuestro estado compartido para este ciclo
    InstanceData.QueryState = MakeShared<FAsyncCoverQueryState>();

    // Creamos un puntero débil para pasarlo al Lambda de forma segura
    TWeakPtr<FAsyncCoverQueryState> WeakQueryState = InstanceData.QueryState;

    FEnvQueryRequest QueryRequest(InstanceData.CoverQuery, ControlledPawn);
    InstanceData.QueryRequestID = QueryRequest.Execute(
        InstanceData.RunMode,
        FQueryFinishedSignature::CreateLambda([WeakQueryState](TSharedPtr<FEnvQueryResult> Result)
            {
                // El Lambda SOLO actualiza los datos, no toca el State Tree directamente
                if (TSharedPtr<FAsyncCoverQueryState> State = WeakQueryState.Pin())
                {
                    State->bIsComplete = true; // Avisamos que terminó

                    if (Result.IsValid() && Result->IsSuccessful())
                    {
                        State->bIsSuccessful = true;
                        State->CoverLocation = Result->GetItemAsLocation(0);
                    }
                }
            })
    );

    // Devolvemos Running para que el State Tree se quede en esta tarea y empiece a llamar a Tick()
    return EStateTreeRunStatus::Running;
}

// 2. Implementamos el Tick, que es el lugar 100% seguro para actualizar el State Tree
EStateTreeRunStatus FStateTreeTask_FindCover::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{
    FInstanceDataType& InstanceData = Context.GetInstanceData<FInstanceDataType>(*this);

    // Si el query está en proceso, seguimos esperando
    if (!InstanceData.QueryState || !InstanceData.QueryState->bIsComplete)
    {
        return EStateTreeRunStatus::Running;
    }

    // Si llegó hasta aquí, el query terminó. Evaluamos el resultado.
    if (InstanceData.QueryState->bIsSuccessful)
    {
        // Guardamos el resultado en la variable final del State Tree
        InstanceData.CoverLocation = InstanceData.QueryState->CoverLocation;
        InstanceData.ExecutionStatus = EStateTreeRunStatus::Succeeded;
        return EStateTreeRunStatus::Succeeded;
    }

    InstanceData.ExecutionStatus = EStateTreeRunStatus::Failed;
    return EStateTreeRunStatus::Failed;
}