#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateStyle.h"

class FGoogleRPCEditorStyle
{
public:
	static void Initialize();
	
	static void Shutdown();

	/** reloads textures used by slate renderer */
	static void ReloadTextures();

	/** @return The Slate style set for the UMG Style */
	static const ISlateStyle& Get();

	static FName GetStyleSetName();

	static const FSlateBrush* GetBrush(FName PropertyName, const ANSICHAR* Specifier = NULL);

private:

	static TSharedRef< class FSlateStyleSet > Create();

private:

	static TSharedPtr< class FSlateStyleSet > GoogleRPCEditorStyleInstance;
};
