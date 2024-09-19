// © 2023 Kaya Adrian.

#pragma once

#include "Layers/AtumLayerBaseOptions.h"
#include "Macros/AtumMacrosGuards.h"

TORCH_INCLUDES_START
#include <torch/nn/options/linear.h>
TORCH_INCLUDES_END

#include "AtumLayerLinearOptions.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerLinearOptions"

/**
 * Options structure for the Linear layer
 */
USTRUCT(BlueprintType, DisplayName = "ATUM Linear Layer Options")
struct ATUM_API FAtumLayerLinearOptions : public FAtumLayerBaseOptions
{
	GENERATED_BODY()
	
	/**
	 * Size of each input sample
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	int64 InFeatures;
	
	/**
	 * Size of each output sample
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	int64 OutFeatures;
	
	/**
	 * Determines if the layer will learn an additive bias or not
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite,  meta = (AllowPrivateAccess))
	bool bBias;
	
	/**
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	FAtumLayerLinearOptions() noexcept;
	
	/**
	 * Returns the layer as the LibTorch object variant by overloading the relevant cast operator
	 */
	[[nodiscard]]
	FORCEINLINE explicit operator torch::nn::LinearOptions() const noexcept
	{ return torch::nn::LinearOptions(InFeatures, OutFeatures).bias(bBias); }
	
	/**
	 * Copies the data from a LibTorch structure
	 * 
	 * @param Options LibTorch-equivalent options instance
	 */
	void SetFrom(const torch::nn::LinearOptions& Options) noexcept;
};

#undef LOCTEXT_NAMESPACE
