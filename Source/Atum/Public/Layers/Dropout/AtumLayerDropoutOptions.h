#pragma once

#include "Layers/AtumLayerBaseOptions.h"
#include "Macros/AtumMacrosGuards.h"

TORCH_INCLUDES_START
#include <torch/nn/options/dropout.h>
TORCH_INCLUDES_END

#include "AtumLayerDropoutOptions.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerDropoutOptions"






USTRUCT(BlueprintType, DisplayName = "ATUM Dropout Layer Options")
struct ATUM_API FAtumLayerDropoutOptions : public FAtumLayerBaseOptions
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	float P;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	bool bInplace;

	UE_NODISCARD_CTOR
	FAtumLayerDropoutOptions() noexcept;

	[[nodiscard]]
	FORCEINLINE explicit operator torch::nn::DropoutOptions() const noexcept
	{ return torch::nn::DropoutOptions(P).inplace(bInplace); }


	void SetFrom(const torch::nn::DropoutOptions& Options) noexcept;
};

#undef LOCTEXT_NAMESPACE