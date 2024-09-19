// © 2023 Kaya Adrian.

#pragma once

#include "Layers/AtumLayerBaseOptions.h"
#include "Macros/AtumMacrosGuards.h"

TORCH_INCLUDES_START
#include <torch/nn/options/linear.h>
TORCH_INCLUDES_END

#include "AtumLayerFlattenOptions.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerFlattenOptions"

/**
 * Options structure for the Flatten layer
 */
USTRUCT(BlueprintType, DisplayName = "ATUM Flatten Layer Options")
struct ATUM_API FAtumLayerFlattenOptions : public FAtumLayerBaseOptions
{
	GENERATED_BODY()
	
	/**
	 * Size index from which to flatten
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	int64 StartDimension;
	
	/**
	 * Size index to which to flatten
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	int64 EndDimension;
	
	/**
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	FAtumLayerFlattenOptions() noexcept;
	
	/**
	 * Returns the layer as the LibTorch object variant by overloading the relevant cast operator
	 */
	[[nodiscard]]
	FORCEINLINE explicit operator torch::nn::FlattenOptions() const noexcept
	{ return torch::nn::FlattenOptions().start_dim(StartDimension).end_dim(EndDimension); }
	
	/**
	 * Copies the data from a LibTorch structure
	 * 
	 * @param Options LibTorch-equivalent options instance
	 */
	void SetFrom(const torch::nn::FlattenOptions& Options) noexcept;
};

#undef LOCTEXT_NAMESPACE
