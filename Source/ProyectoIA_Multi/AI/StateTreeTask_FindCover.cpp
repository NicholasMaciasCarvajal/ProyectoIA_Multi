#include "AI/StateTreeTask_FindCover.h"
#include "AI/CustomAIController.h" 
#include "StateTreeExecutionContext.h"
#include "Components/StateTreeComponent.h"
#include "AIController.h"
#include "EnvironmentQuery/EnvQueryManager.h"

FStateTreeTask_FindCover::FStateTreeTask_FindCover()
{
    bShouldCallTick = true;
}

EStateTreeRunStatus FStateTreeTask_FindCover::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
    FInstanceDataType& InstanceData = Context.GetInstanceData<FInstanceDataType>(*this);
    InstanceData.ExecutionStatus = EStateTreeRunStatus::Running;

    // Asignar el controlador solo si no venía enlazado desde el Editor
    if (!InstanceData.AIController)
    {
        InstanceData.AIController = Cast<AAIController>(Context.GetOwner());
    }

    if (!InstanceData.CoverQuery || !InstanceData.AIController)
    {
        return EStateTreeRunStatus::Failed;
    }

    APawn* ControlledPawn = InstanceData.AIController->GetPawn();
    if (!ControlledPawn)
    {
        return EStateTreeRunStatus::Failed;
    }

    InstanceData.QueryState = MakeShared<FAsyncCoverQueryState>();
    TWeakPtr<FAsyncCoverQueryState> WeakQueryState = InstanceData.QueryState;

    FEnvQueryRequest QueryRequest(InstanceData.CoverQuery, ControlledPawn);
    InstanceData.QueryRequestID = QueryRequest.Execute(
        InstanceData.RunMode,
        FQueryFinishedSignature::CreateLambda([WeakQueryState](TSharedPtr<FEnvQueryResult> Result)
            {
                if (TSharedPtr<FAsyncCoverQueryState> State = WeakQueryState.Pin())
                {
                    State->bIsComplete = true;

                    // Validación de seguridad para evitar Crash si la lista está vacía
                    if (Result.IsValid() && Result->IsSuccessful() && Result->Items.Num() > 0)
                    {
                        State->bIsSuccessful = true;
                        State->CoverLocation = Result->GetItemAsLocation(0);
                    }
                }
            })
    );

    return EStateTreeRunStatus::Running;
}

EStateTreeRunStatus FStateTreeTask_FindCover::Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const
{
    FInstanceDataType& InstanceData = Context.GetInstanceData<FInstanceDataType>(*this);

    if (!InstanceData.QueryState || !InstanceData.QueryState->bIsComplete)
    {
        return EStateTreeRunStatus::Running;
    }

    if (InstanceData.QueryState->bIsSuccessful)
    {
        InstanceData.CoverLocation = InstanceData.QueryState->CoverLocation;
        InstanceData.ExecutionStatus = EStateTreeRunStatus::Succeeded;

        if (ACustomAIController* AICtrl = Cast<ACustomAIController>(InstanceData.AIController))
        {
            AICtrl->CoverLocation = InstanceData.CoverLocation;
        }

        return EStateTreeRunStatus::Succeeded;
    }

    InstanceData.ExecutionStatus = EStateTreeRunStatus::Failed;
    return EStateTreeRunStatus::Failed;
}

void FStateTreeTask_FindCover::ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const
{
    FInstanceDataType& InstanceData = Context.GetInstanceData<FInstanceDataType>(*this);

    if (InstanceData.QueryRequestID != INDEX_NONE)
    {
        if (UEnvQueryManager* EQS = UEnvQueryManager::GetCurrent(Context.GetWorld()))
        {
            EQS->AbortQuery(InstanceData.QueryRequestID);
        }
        InstanceData.QueryRequestID = INDEX_NONE;
    }
    InstanceData.QueryState.Reset();
}