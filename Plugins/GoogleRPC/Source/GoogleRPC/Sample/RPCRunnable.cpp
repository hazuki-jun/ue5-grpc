#include "RPCRunnable.h"

FRPCRunnable::FRPCRunnable()
{
	bIsRunning = true;
	ThreadID = 0;
	RunnableThread = nullptr;
}

FRPCRunnable::FRPCRunnable(const FString& InThreadName)
{
	bIsRunning = true;
	ThreadName = InThreadName;
	ThreadID = 0;
	RunnableThread = nullptr;
}

uint32 FRPCRunnable::Run()
{
	FPlatformProcess::Sleep(0.1f);
	while (bIsRunning)
	{
		FPlatformProcess::Sleep(0.1f);
	}
	
	return 0;
}

void FRPCRunnable::ShowDown()
{
	bIsRunning = false;
	if (RunnableThread)
	{
		RunnableThread->Kill(false);
	}
}
