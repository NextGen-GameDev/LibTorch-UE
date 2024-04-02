// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Layers/IAtumLayer.h"
#include "Macros/AtumMacrosLayer.h"
#include "Models/Llama/llama_causal_lm.h"
#include "Models/Llama/AtumLlamaOptions.h"
TORCH_INCLUDES_START
#include <torch/torch.h>
TORCH_INCLUDES_END

#include "LlamaUnreal.generated.h"

#define LOCTEXT_NAMESPACE "AtumLlamaUnreal"



/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class ATUM_API ULlamaUnreal : public UObject, public IAtumLayer
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER(FAtumLlamaOptions, LlamaCausalLM)



public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Layer")
	bool Generate(const TScriptInterface<IAtumTensor>& Input, TScriptInterface<IAtumTensor>& Output, const int32& NumNewTokens);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Layer")
	bool LoadParams(const FString& Path);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Layer")
	bool ToArchive(const FString& InPath, const FString& OutPath);

	UFUNCTION(BlueprintCallable, Category = "ATUM|Layer")
	void SetOptions(const FAtumLlamaOptions& NewOptions);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess, ShowOnlyInnerProperties, ExposeOnSpawn))
	FAtumLlamaOptions Options;

};

#undef LOCTEXT_NAMESPACE