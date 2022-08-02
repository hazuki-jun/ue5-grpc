// Copyright Epic Games, Inc. All Rights Reserved.

#include "GoogleRPCEditor.h"

#include "GoogleRPCEditorCommand.h"
#include "GoogleRPCEditorStyle.h"
#include "LevelEditor.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FGoogleRPCEditorModule"

void FGoogleRPCEditorModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	FGoogleRPCEditorStyle::Initialize();
	FGoogleRPCEditorStyle::ReloadTextures();

	FGoogleRPCEditorCommand::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	// 菜单按钮事件
	PluginCommands->MapAction(
		FGoogleRPCEditorCommand::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FGoogleRPCEditorModule::PluginButtonClicked),
		FCanExecuteAction());

	// 注册菜单
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
	MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FGoogleRPCEditorModule::AddMenuExtension));
	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	
	// {
	// 	TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
	// 	ToolbarExtender->AddToolBarExtension("Tools", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FGoogleRPCEditorModule::AddToolbarExtension));
	// 	
	// 	LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	// }
	
}

void FGoogleRPCEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FGoogleRPCEditorStyle::Shutdown();
	FGoogleRPCEditorCommand::Unregister();
}

void FGoogleRPCEditorModule::PluginButtonClicked()
{
	RegenerateAllPBFiles();
}

void FGoogleRPCEditorModule::RegenerateAllPBFiles()
{
	const FString Path= FPaths::GameSourceDir() / "Proto";
	DeleteAllPBFiles(Path);
	GenerateAllPBFiles(GetProtocExecPath(), Path);
}

void FGoogleRPCEditorModule::DeleteAllPBFiles(const FString& Path)
{
	if (!FPaths::DirectoryExists(Path))
	{
		return;
	}

	TArray<FString> AllProtoCodeFiles;

	auto SearchSuffixFiles = [=,&AllProtoCodeFiles](const FString& pSuffix)
	{
		IFileManager::Get().FindFilesRecursive(AllProtoCodeFiles, *Path, *pSuffix, true, false, false);
	};

	for (const FString& Suffix : { TEXT("*.pb.cc") ,TEXT("*.pb.h") ,TEXT("*.pb.cpp") })
	{
		SearchSuffixFiles(Suffix);
	}

	for (const auto& File : AllProtoCodeFiles)
	{
		if (FPaths::FileExists(File))
		{
			IFileManager::Get().Delete(*File, true);
		}
	}
	
}

void FGoogleRPCEditorModule::GenerateAllPBFiles(const FString &ExecDirectory, const FString& Path)
{
	TArray<FString> AllFiles;
	TArray<FString> ProtocCommands;
	TArray<FString> ProtocPluginCommands;
	IFileManager::Get().FindFilesRecursive(AllFiles, *Path, TEXT("*.proto"),true,false,true);
	for (const auto& ProtoFile : AllFiles)
	{
		FString FilePath = ProtoFile;
		{
			int32 Pos;
			if (FilePath.FindLastChar('/', Pos))
			{
				FilePath.RemoveAt(Pos, FilePath.Len() - Pos);
			}
		}

		FString OtherParam = (TEXT("--proto_path=\"") + FilePath + TEXT("\"")) +  (TEXT(" \"") + ProtoFile +TEXT("\"") + TEXT(" "));
		FString OutPath = TEXT("\"") + FilePath + TEXT("\"");
		
		FString OutCPP = OtherParam + TEXT("--cpp_out=") + OutPath;
		ProtocCommands.Add(MoveTemp(OutCPP));

		FString PluginPath = ExecDirectory / "grpc_cpp_plugin.exe";
		FString OutRPC = OtherParam + TEXT("--plugin=protoc-gen-grpc=") + TEXT("\"") + PluginPath + TEXT("\"") + TEXT(" --grpc_out=") + OutPath;
		ProtocPluginCommands.Add(MoveTemp(OutRPC));
	}

	bool bGenerateSuccess = true;

	// 生成pb文件
	for (const auto& Command : ProtocCommands)
	{
		FProcHandle ProtocProcIns = FPlatformProcess::CreateProc(*(ExecDirectory / "protoc.exe"), *Command, true, false, NULL, NULL, NULL, NULL, NULL);
		if (!ProtocProcIns.IsValid())
		{
			bGenerateSuccess = false;
			break;
		}
	}

	if (bGenerateSuccess)
	{
		// 生成 grpc.pb 文件
		for (const auto& ProtocPluginCommand : ProtocPluginCommands)
		{
			FProcHandle ProtocProcIns = FPlatformProcess::CreateProc(*(ExecDirectory / "protoc.exe"), *ProtocPluginCommand, true, false, NULL, NULL, NULL, NULL, NULL);
			if (!ProtocProcIns.IsValid())
			{
				bGenerateSuccess = false;
				break;
			}
		}
	}

	if (!bGenerateSuccess)
	{
		UE_LOG(LogTemp, Warning, TEXT("*********** Generate Proto files failed ************ "))
	}
}

FString FGoogleRPCEditorModule::GetProtocExecPath() const
{
	FString RetPath;
	FString PluginPath = IPluginManager::Get().FindPlugin(TEXT("GoogleRPC"))->GetBaseDir();
	PluginPath.Append(TEXT(""));
	FString ExecPath = FPaths::Combine(PluginPath, TEXT("ThirdParty/bin"));
	return ExecPath;
}

void FGoogleRPCEditorModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FGoogleRPCEditorCommand::Get().PluginAction);
}

void FGoogleRPCEditorModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FGoogleRPCEditorCommand::Get().PluginAction);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGoogleRPCEditorModule, GoogleRPCEditor)