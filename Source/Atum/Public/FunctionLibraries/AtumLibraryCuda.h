// © 2023 Kaya Adrian.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Macros/AtumMacrosGuards.h"

TORCH_INCLUDES_START
#include <torch/cuda.h>
TORCH_INCLUDES_END

#include "AtumLibraryCuda.generated.h"


#define LOCTEXT_NAMESPACE "AtumLibraryCuda"

/**
 * Collection of Blueprint functions related to CUDA
 */
UCLASS(Abstract, Blueprintable, BlueprintType, DisplayName = "ATUM CUDA Library")
class ATUM_API UAtumLibraryCuda : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/**
	 * Checks if CUDA can be used
	 * 
	 * @return Is CUDA available?
	 */
	[[nodiscard]]
	UFUNCTION(BlueprintPure, Category = "ATUM|CUDA")
	static FORCEINLINE bool IsCudaAvailable() noexcept { return torch::cuda::is_available(); }
	
	/**
	 * Checks if cuDNN can be used
	 * 
	 * @return Is cuDNN available?
	 */
	[[nodiscard]]
	UFUNCTION(BlueprintPure, Category = "ATUM|CUDA")
	static FORCEINLINE bool IsCudnnAvailable() noexcept { return torch::cuda::cudnn_is_available(); }
};

#undef LOCTEXT_NAMESPACE
