#pragma once

#include "Layers/AtumLayerBaseOptions.h"
#include "Macros/AtumMacrosGuards.h"

TORCH_INCLUDES_START
#include <torch/nn/options/activation.h>
TORCH_INCLUDES_END

#include "AtumLayerGeluOptions.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerGeluOptions"

USTRUCT(BlueprintType, DisplayName = "ATUM GELU Layer Options")
struct ATUM_API FAtumLayerOptionsGelu : public FAtumLayerBaseOptions
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	FString Approximate = "none";
	
	UE_NODISCARD_CTOR
	FAtumLayerOptionsGelu() noexcept;
	
	[[nodiscard]]
	FORCEINLINE explicit operator torch::nn::GELUOptions() const noexcept
	{ return torch::nn::GELUOptions().approximate(TCHAR_TO_UTF8(*Approximate)); }
	
	FORCEINLINE void SetFrom(const torch::nn::GELUOptions& Options) noexcept
	{ Approximate = UTF8_TO_TCHAR(Options.approximate().c_str()); }
};

#undef LOCTEXT_NAMESPACE

