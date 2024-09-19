#pragma once

#include "Layers/AtumLayerBaseOptions.h"
#include "Macros/AtumMacrosGuards.h"

TORCH_INCLUDES_START
#include <torch/nn/options/embedding.h>
TORCH_INCLUDES_END

#include "AtumLayerEmbedOptions.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerEmbedOptions"

USTRUCT(BlueprintType, DisplayName = "ATUM Embedding Layer Options")
struct ATUM_API FAtumLayerEmbedOptions : public FAtumLayerBaseOptions
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	int64 NumEmbeddings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	int64 EmbeddingDim;

	UE_NODISCARD_CTOR
	FAtumLayerEmbedOptions() noexcept;

	[[nodiscard]]
	FORCEINLINE explicit operator torch::nn::EmbeddingOptions() const noexcept
	{ return torch::nn::EmbeddingOptions(NumEmbeddings, EmbeddingDim); }

	void SetFrom(const torch::nn::EmbeddingOptions& Options) noexcept;
};

#undef LOCTEXT_NAMESPACE