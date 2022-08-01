// Fill out your copyright notice in the Description page of Project Settings.


#include "TestServerActor.h"

#include "ClientRunnable.h"

// Sets default values
ATestServerActor::ATestServerActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	ServerRunnable = nullptr;
}

void ATestServerActor::RunServer()
{
	ServerRunnable = FServerRunnable::Create<FServerRunnable>("ServerRunnable");
}

// Called when the game starts or when spawned
void ATestServerActor::BeginPlay()
{
	Super::BeginPlay();
}

void ATestServerActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	ServerRunnable->ShowDown();
	
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void ATestServerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

