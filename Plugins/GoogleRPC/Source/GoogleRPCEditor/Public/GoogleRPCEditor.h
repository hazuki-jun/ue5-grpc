// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FGoogleRPCEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void PluginButtonClicked();
	void AddMenuExtension(FMenuBuilder& Builder);
	void AddToolbarExtension(FToolBarBuilder& Builder);

	void RegenerateAllPBFiles();
	// 删除pb文件
	void DeleteAllPBFiles(const FString& Path);
	// 生成pb文件
	void GenerateAllPBFiles(const FString &ExecDirectory, const FString &Path);
	
	FString GetProtocExecPath() const;
private:
	TSharedPtr<class FUICommandList> PluginCommands;
};
