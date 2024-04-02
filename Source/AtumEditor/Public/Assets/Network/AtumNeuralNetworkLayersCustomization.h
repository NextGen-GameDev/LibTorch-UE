// © 2024 Chong-U Lim
#pragma once

#include "IDetailCustomization.h"
#include "Dom/JsonObject.h"
#include "CoreMinimal.h"
#include "Macros/AtumMacrosGuards.h"

TORCH_INCLUDES_START
#include <c10/util/Optional.h>
TORCH_INCLUDES_END

class UAtumNeuralNetworkLayers;
class ULlamaUnreal;

#define LOCTEXT_NAMESPACE "LlamaUnrealCustomization"

class FAtumNeuralNetworkLayersCustomization : public IDetailCustomization
{
public:
	static TSharedRef<IDetailCustomization> MakeInstance();

	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

	static c10::optional<int32> GetJsonIntField(const TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName, c10::optional<int32> DefaultValue);
	static bool GetJsonBoolField(const TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName, bool DefaultValue);

private:
	void OnJsonFilePathPicked(const FString& FilePath, ULlamaUnreal* LlamaUnreal);
	void LoadConfigurationFromFile(ULlamaUnreal* LlamaUnreal);
};

#undef LOCTEXT_NAMESPACE