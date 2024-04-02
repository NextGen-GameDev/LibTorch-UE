#pragma once

#include "Assets/Network/AtumNeuralNetworkLayersCustomization.h"

#include "DesktopPlatformModule.h"
#include "DetailLayoutBuilder.h"
#include "Models/Llama/LlamaUnreal.h"
#include "Models/Llama/llama_config.h"
#include "DetailWidgetRow.h"
#include "IDesktopPlatform.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Layers/Network/AtumNeuralNetworkLayers.h"
#include "Misc/FileHelper.h"
#include "Json.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SFilePathPicker.h"


TSharedRef<IDetailCustomization> FAtumNeuralNetworkLayersCustomization::MakeInstance()
{
    return MakeShareable(new FAtumNeuralNetworkLayersCustomization());
}

void FAtumNeuralNetworkLayersCustomization::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
   TArray<TWeakObjectPtr<UObject>> Objects;
    DetailBuilder.GetObjectsBeingCustomized(Objects);

    // Loop over each object being customized
    for (const TWeakObjectPtr<UObject>& Object : Objects)
    {
        if (UAtumNeuralNetworkLayers* Layers = Cast<UAtumNeuralNetworkLayers>(Object.Get()))
        {
            // Get the property handles for LayerTypes and LayerObjects
            TSharedPtr<IPropertyHandle> LayerTypesPropertyHandle = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UAtumNeuralNetworkLayers, LayerTypes), UAtumNeuralNetworkLayers::StaticClass());
            TSharedPtr<IPropertyHandle> LayerObjectsPropertyHandle = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UAtumNeuralNetworkLayers, LayerObjects), UAtumNeuralNetworkLayers::StaticClass());

            // Create a category for LayerTypes and display its default property widget
            IDetailCategoryBuilder& LayerTypesCategory = DetailBuilder.EditCategory("Layer Types", FText::GetEmpty(), ECategoryPriority::Important);
            LayerTypesCategory.AddProperty(LayerTypesPropertyHandle);

            if (LayerObjectsPropertyHandle.IsValid())
            {
                uint32 NumChildren;
                LayerObjectsPropertyHandle->GetNumChildren(NumChildren);

                for (uint32 i = 0; i < NumChildren; i++)
                {
                    TSharedPtr<IPropertyHandle> ChildHandle = LayerObjectsPropertyHandle->GetChildHandle(i);
                    if (ChildHandle.IsValid())
                    {
                        UObject* LayerObject = nullptr;
                        ChildHandle->GetValue(LayerObject);

                        if (ULlamaUnreal* LlamaUnreal = Cast<ULlamaUnreal>(LayerObject))
                        {
                            // Create a new category for each LlamaUnreal object
                            FString CategoryName = FString::Printf(TEXT("Layer Object %d"), i);
                            IDetailCategoryBuilder& LayerObjectCategory = DetailBuilder.EditCategory(*CategoryName, FText::GetEmpty(), ECategoryPriority::Important);

                            // Add a custom row for the 'Load JSON' button at the top of the category
                            LayerObjectCategory.AddCustomRow(FText::FromString("Llama Configuration"))
                                .WholeRowContent()
                                [
                                    SNew(SHorizontalBox)
                                    + SHorizontalBox::Slot()
                                    .AutoWidth()
                                    [
                                        SNew(SButton)
                                        .Text(FText::FromString("Load options from JSON"))
                                        .OnClicked(FOnClicked::CreateLambda([this, LlamaUnreal]() -> FReply {
                                            // Implement the logic to load the JSON file and set the values in the LlamaUnreal object
                                            // You can use the existing SetFromFile function or create a new one specifically for this purpose
                                            // LlamaUnreal->SetFromFile(FilePath);
                                            if (LlamaUnreal)
                                            {
                                                LoadConfigurationFromFile(LlamaUnreal);
                                            }
                                            return FReply::Handled();
                                        }))
                                    ]
                                ];

                            // Add the default property widget for this LlamaUnreal object
                            LayerObjectCategory.AddProperty(ChildHandle);
                        }
                    }
                }
            }
        }
    }
}

void FAtumNeuralNetworkLayersCustomization::OnJsonFilePathPicked(const FString& FilePath, ULlamaUnreal* LlamaUnreal)
{
    // Implement the logic to load the JSON file and set the values in the LlamaUnreal object
    // You can use the existing SetFromFile function or create a new one specifically for this purpose
    // LlamaUnreal->SetFromFile(FilePath);
}

void FAtumNeuralNetworkLayersCustomization::LoadConfigurationFromFile(ULlamaUnreal* LlamaUnreal)
{
    IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
    if (DesktopPlatform)
    {
        TArray<FString> OpenFilenames;
        DesktopPlatform->OpenFileDialog(
            nullptr, // Parent window handle
            TEXT("Load JSON"), // Dialog title
            TEXT(""), // Default path
            TEXT(""), // Default file name
            TEXT("JSON files (*.json)|*.json"), // File types
            EFileDialogFlags::None,
            OpenFilenames
        );

        if (OpenFilenames.Num() > 0)
        {
            const FString& FilePath = OpenFilenames[0];
            FString JsonRaw;
            if (FFileHelper::LoadFileToString(JsonRaw, *FilePath))
            {
                TSharedPtr<FJsonObject> JsonObject;
                TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonRaw);

                if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
                {
                    // Parse the JSON and apply settings to create a new FLlamaConfig instance
                    LlamaConfig Config;

                    // Set Config fields from JsonObject
                    Config.vocab_size = JsonObject->GetIntegerField(TEXT("vocab_size"));
                    Config.hidden_size = JsonObject->GetIntegerField(TEXT("hidden_size"));
                    Config.intermediate_size = JsonObject->GetIntegerField(TEXT("intermediate_size"));
                    Config.num_hidden_layers = JsonObject->GetIntegerField(TEXT("num_hidden_layers"));
                    Config.num_attention_heads = JsonObject->GetIntegerField(TEXT("num_attention_heads"));
                    Config.hidden_act = std::string(TCHAR_TO_UTF8(*JsonObject->GetStringField(TEXT("hidden_act"))));
                    Config.max_position_embeddings = JsonObject->GetIntegerField(TEXT("max_position_embeddings"));
                    Config.initializer_range = JsonObject->GetNumberField(TEXT("initializer_range"));
                    Config.rms_norm_eps = JsonObject->GetNumberField(TEXT("rms_norm_eps"));
                    Config.use_cache = JsonObject->GetBoolField(TEXT("use_cache"));

                    
                    Config.pad_token_id = GetJsonIntField(JsonObject, TEXT("pad_token_id"), c10::nullopt);
                    Config.bos_token_id = GetJsonIntField(JsonObject, TEXT("bos_token_id"), Config.bos_token_id).value();
                    Config.eos_token_id = GetJsonIntField(JsonObject, TEXT("eos_token_id"), Config.eos_token_id).value();

                    Config.tie_word_embeddings = GetJsonBoolField(JsonObject, TEXT("tie_word_embeddings"), Config.tie_word_embeddings);
                    
                    Config.output_hidden_states = GetJsonBoolField(JsonObject, TEXT("output_hidden_states"), Config.output_hidden_states);

                    Config.output_attentions = GetJsonBoolField(JsonObject, TEXT("output_attentions"), Config.output_attentions);

                    // Apply the new Config to the LlamaUnreal instance
                    FAtumLlamaOptions NewOptions;
                    NewOptions.SetFrom(Config);
                    LlamaUnreal->SetOptions(NewOptions);

                    // Refresh the UI to reflect the loaded values
                    FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
                    TSharedPtr<IDetailsView> DetailsView = PropertyEditorModule.FindDetailView(TEXT("AtumNeuralNetworkEditorDetailsTab"));
                    if (DetailsView.IsValid())
                    {
                        DetailsView->SetObject(LlamaUnreal, true);
                    }   
                }
            }
        }
    }
}




c10::optional<int32> FAtumNeuralNetworkLayersCustomization::GetJsonIntField(const TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName, c10::optional<int32> DefaultValue)
{
    if (JsonObject->HasField(FieldName))
    {
        return JsonObject->GetIntegerField(FieldName);
    }
    return DefaultValue;
}

bool FAtumNeuralNetworkLayersCustomization::GetJsonBoolField(const TSharedPtr<FJsonObject>& JsonObject, const FString& FieldName, bool DefaultValue)
{
    if (JsonObject->HasField(FieldName))
    {
        return JsonObject->GetBoolField(FieldName);
    }
    return DefaultValue;
}
