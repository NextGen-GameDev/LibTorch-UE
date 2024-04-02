// © 2023 Kaya Adrian.

#include "AtumEditorModule.h"

#include "PropertyEditorModule.h"
#include "Assets/Network/AssetTypeActions_AtumNeuralNetwork.h"
#include "Assets/Network/AtumNeuralNetworkLayersCustomization.h"


#define LOCTEXT_NAMESPACE "AtumEditorModule"

void FAtumEditorModule::StartupModule()
{
	IAssetTools& AssetTools = FAssetToolsModule::GetModule().Get();
	AtumAssetCategoryBit = AssetTools.RegisterAdvancedAssetCategory(
		TEXT("ATUM"),
		LOCTEXT("AtumAssetCategory", "Machine Learning")
	);
	AssetTools.RegisterAssetTypeActions(AtumNeuralNetworkAssetTypeActions);

	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomClassLayout("AtumNeuralNetworkLayers", FOnGetDetailCustomizationInstance::CreateStatic(&FAtumNeuralNetworkLayersCustomization::MakeInstance));
}

void FAtumEditorModule::ShutdownModule()
{
	if (FAssetToolsModule::IsModuleLoaded())
	{
		FAssetToolsModule::GetModule().Get().UnregisterAssetTypeActions(AtumNeuralNetworkAssetTypeActions);
	}

	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
		PropertyModule.UnregisterCustomClassLayout("AtumNeuralNetworkLayers");
	}
}
	
IMPLEMENT_MODULE(FAtumEditorModule, AtumEditor)

#undef LOCTEXT_NAMESPACE
