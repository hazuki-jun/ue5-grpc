// Fill out your copyright notice in the Description page of Project Settings.


#include "ClientRunnable.h"

#include "HelloWorld/greeter_client.cc"
#include "HelloWorld/greeter_server.cc"

FClientRunnable::FClientRunnable(const FString& InThreadName) : FRPCRunnable(InThreadName)
{
	m_client = nullptr;
}

uint32 FClientRunnable::Run()
{
	m_client = new GreeterClient(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
	return FRPCRunnable::Run();
}

void FClientRunnable::RequestMessage(const FString& Message)
{
	if (m_client)
	{
		std::string user(TCHAR_TO_UTF8(*Message));
		FString Reply = m_client->SayHello(user).c_str();

		AsyncTask(ENamedThreads::GameThread, [=]()
		{
			RPCDelegate.ExecuteIfBound(Message);
		});
	}
}

void FServerRunnable::Exit()
{
	GreeterService::ShowDown();
}

void FServerRunnable::ShowDown()
{
	GreeterService::ShowDown();
	FRPCRunnable::ShowDown();
}

uint32 FServerRunnable::Run()
{
	GreeterService::RunServer();
	
	return FRPCRunnable::Run();
}
