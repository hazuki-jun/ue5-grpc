#include "GoogleRPCEditorStyle.h"

#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleRegistry.h"

TSharedPtr< FSlateStyleSet > FGoogleRPCEditorStyle::GoogleRPCEditorStyleInstance = nullptr;

void FGoogleRPCEditorStyle::Initialize()
{
	Get();
}

void FGoogleRPCEditorStyle::Shutdown()
{
	if (GoogleRPCEditorStyleInstance.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*GoogleRPCEditorStyleInstance);
		ensure(GoogleRPCEditorStyleInstance.IsUnique());
		GoogleRPCEditorStyleInstance.Reset();
	}
}

void FGoogleRPCEditorStyle::ReloadTextures()
{
	FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
}

const ISlateStyle& FGoogleRPCEditorStyle::Get()
{
	if (!GoogleRPCEditorStyleInstance.IsValid())
	{
		GoogleRPCEditorStyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*GoogleRPCEditorStyleInstance);
	}
	return *GoogleRPCEditorStyleInstance;
}

FName FGoogleRPCEditorStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("GoogleRPCEditorStyle"));
	return StyleSetName;
}

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BOX_BRUSH( RelativePath, ... ) FSlateBoxBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define BORDER_BRUSH( RelativePath, ... ) FSlateBorderBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )
#define DEFAULT_FONT(...) FCoreStyle::GetDefaultFontStyle(__VA_ARGS__)

const FVector2D Icon20x20(20.0f, 20.0f);
const FVector2D Icon40x40(40.0f, 40.0f);
const FVector2D Icon64x64(200.0f, 200.0f);
const FVector2D Icon512x512(512.0f, 512.0f);

TSharedRef<FSlateStyleSet> FGoogleRPCEditorStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("GoogleRPCEditorStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("GoogleRPC")->GetBaseDir() / TEXT("Resources"));

	Style->Set("GoogleRPCEditor.PluginAction", new IMAGE_BRUSH(TEXT("grpc_logo_x40"), Icon40x40));

	return Style;
}

const FSlateBrush* FGoogleRPCEditorStyle::GetBrush(FName PropertyName, const ANSICHAR* Specifier)
{
	return nullptr;
}

#undef IMAGE_BRUSH
#undef BOX_BRUSH
#undef BORDER_BRUSH
#undef DEFAULT_FONT