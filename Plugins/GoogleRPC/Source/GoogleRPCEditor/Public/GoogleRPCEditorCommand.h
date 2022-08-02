#pragma once
#include "GoogleRPCEditorStyle.h"

class FGoogleRPCEditorCommand : public TCommands<FGoogleRPCEditorCommand> 
{
public:
	FGoogleRPCEditorCommand()
	: TCommands<FGoogleRPCEditorCommand>(TEXT("GoogleRPCEditor"), NSLOCTEXT("Contexts", "GoogleRPCEditor", "GoogleRPCEditor Plugin"), NAME_None, FGoogleRPCEditorStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

	TSharedPtr<FUICommandInfo> PluginAction;
};
