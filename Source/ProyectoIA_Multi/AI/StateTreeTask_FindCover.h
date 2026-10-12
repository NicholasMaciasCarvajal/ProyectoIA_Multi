// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateTreeTaskBase.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "StateTreeTask_FindCover.generated.h"

class UEnvQuery;
class AAIController;
class UStateTreeComponent;

// Estructura auxiliar para compartir datos del EQS asíncrono sin bloquear el hilo principal
struct FAsyncCoverQueryState
{
	bool bIsComplete = false;
	bool bIsSuccessful = false;
	FVector CoverLocation = FVector::ZeroVector;
};

USTRUCT()
struct FStateTreeTask_FindCoverInstanceData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = "StateTree")
	TObjectPtr<AAIController> AIController = nullptr;

	UPROPERTY(EditAnywhere, Category = "StateTree")
	TObjectPtr<UEnvQuery> CoverQuery = nullptr;

	UPROPERTY(EditAnywhere, Category = "Output")
	FVector CoverLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, Category = "Parameter")
	TEnumAsByte<EEnvQueryRunMode::Type> RunMode = EEnvQueryRunMode::SingleResult;

	int32 QueryRequestID = INDEX_NONE;
	EStateTreeRunStatus ExecutionStatus = EStateTreeRunStatus::Running;

	// Puntero compartido runtime para comunicarse con el Lambda del EQS (sin UPROPERTY)
	TSharedPtr<FAsyncCoverQueryState> QueryState;
};

USTRUCT(meta = (DisplayName = "Find Cover (EQS)", Category = "AI|Cover"))
struct PROYECTOIA_MULTI_API FStateTreeTask_FindCover : public FStateTreeTaskCommonBase
{
	GENERATED_BODY()

	FStateTreeTask_FindCover();

	using FInstanceDataType = FStateTreeTask_FindCoverInstanceData;
	virtual const UStruct* GetInstanceDataType() const override { return FInstanceDataType::StaticStruct(); }

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
	virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) const override;

	virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) const override;
};