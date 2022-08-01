// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPCRunnable.h"

/**
 * 
 */
class GOOGLERPC_API FClientRunnable : public FRPCRunnable
{
public:
	FClientRunnable(const FString& InThreadName);
	virtual uint32 Run() override;
	void RequestMessage(const FString& Message);
protected:
	class GreeterClient* m_client;
};

/**
 * 
 */
class GOOGLERPC_API FServerRunnable : public FRPCRunnable
{
public:
	FServerRunnable(const FString& InThreadName) : FRPCRunnable(InThreadName) {}
	virtual void Exit() override;
	virtual void ShowDown() override;
	virtual uint32 Run() override;
};
