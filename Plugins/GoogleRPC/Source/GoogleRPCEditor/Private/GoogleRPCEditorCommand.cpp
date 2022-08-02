#include "GoogleRPCEditorCommand.h"

#define LOCTEXT_NAMESPACE "FGoogleRPCEditorModule"

void FGoogleRPCEditorCommand::RegisterCommands()
{
	UI_COMMAND(PluginAction, "GoogleRPC", "Generate pb files", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
