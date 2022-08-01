// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestServerActor.generated.h"

UCLASS()
class GOOGLERPC_API ATestServerActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATestServerActor();

	UFUNCTION(BlueprintCallable)
	void RunServer();
protected:
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	class FServerRunnable* ServerRunnable;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
