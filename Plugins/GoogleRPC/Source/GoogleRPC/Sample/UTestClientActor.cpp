// Fill out your copyright notice in the Description page of Project Settings.


#include "UTestClientActor.h"

#include "ClientRunnable.h"


// Sets default values
AUTestClientActor::AUTestClientActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ClientRunnable = nullptr;
}

// Called when the game starts or when spawned
void AUTestClientActor::BeginPlay()
{
	Super::BeginPlay();
}

void AUTestClientActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	if (ClientRunnable)
	{
		ClientRunnable->ShowDown();
	}
}

void AUTestClientActor::RunClient()
{
	ClientRunnable = FClientRunnable::Create<FClientRunnable>("ClientRunnable");
	ClientRunnable->RPCDelegate.BindUObject(this, &ThisClass::OnReply);
}

void AUTestClientActor::RequestMessage(const FString& Message)
{
	if (ClientRunnable)
	{
		ClientRunnable->RequestMessage(Message);
	}
}

void AUTestClientActor::OnReply(const FString& Reply)
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Blue, Reply);
	Receive_OnReply(Reply);
}

// Called every frame
void AUTestClientActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

