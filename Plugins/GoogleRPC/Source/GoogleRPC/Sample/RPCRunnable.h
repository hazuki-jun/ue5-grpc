#pragma once

#include "CoreMinimal.h"

class GOOGLERPC_API FRPCRunnable : FRunnable
{
public:
	FRPCRunnable();
	FRPCRunnable(const FString& InThreadName);

	template<class T>
	static T* Create(const FString& InThreadName);

	virtual uint32 Run() override;
	
	virtual void ShowDown();
protected:
	FString ThreadName;
	uint8  bIsRunning;
	uint32 ThreadID;
	FRunnableThread* RunnableThread;
};

template <class T>
T* FRPCRunnable::Create(const FString& InThreadName)
{
	T *Runnable = new T(InThreadName); 
	const auto ThreadIns = FRunnableThread::Create(Runnable, *InThreadName, 0, TPri_Normal);
	Runnable->ThreadID = ThreadIns->GetThreadID();
	Runnable->RunnableThread = ThreadIns;
	return Runnable;
}
