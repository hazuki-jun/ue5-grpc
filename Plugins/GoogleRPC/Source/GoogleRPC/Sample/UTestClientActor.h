// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UTestClientActor.generated.h"

UCLASS()
class GOOGLERPC_API AUTestClientActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AUTestClientActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	UFUNCTION(BlueprintCallable)
	void RunClient();

	UFUNCTION(BlueprintCallable)
	void RequestMessage(const FString& Message);
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
protected:
	class FClientRunnable* ClientRunnable;
};
