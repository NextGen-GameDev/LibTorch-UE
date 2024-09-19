// © 2023 Kaya Adrian.

#pragma once

#include "Macros/AtumMacrosGuards.h"
#include "Optimizers/AtumOptimizerBaseOptions.h"

TORCH_INCLUDES_START
#include <torch/optim/adam.h>
TORCH_INCLUDES_END

#include "AtumOptimizerAdamOptions.generated.h"


#define LOCTEXT_NAMESPACE "AtumOptimizerAdamOptions"

/**
 * Options structure for the Adam optimiser
 */
USTRUCT(BlueprintType, DisplayName = "ATUM Adam Optimizer Options")
struct ATUM_API FAtumOptimizerAdamOptions : public FAtumOptimizerBaseOptions
{
	GENERATED_BODY()
	
	/**
	 * Learning rate
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	double Lr;
	
	/**
	 * Two coefficients that compute running averages of the gradient and its square
	 */
	UPROPERTY(EditFixedSize, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TArray<double> Betas;
	
	/**
	 * Smoothing term for stability
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	double Eps;
	
	/**
	 * Penalty added to the loss function
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	double WeightDecay;
	
	/**
	 * Controls whether or not the AMSGrad variant of the algorithm should be used
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	bool Amsgrad;
	
	/**
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	FAtumOptimizerAdamOptions() noexcept;
	
	/**
	 * Returns the optimiser as the LibTorch object variant by overloading the relevant cast operator
	 */
	[[nodiscard]]
	explicit operator torch::optim::AdamOptions() const noexcept;
	
	/**
	 * Copies the data from a LibTorch structure
	 * 
	 * @param Options LibTorch-equivalent options instance
	 */
	void SetFrom(const torch::optim::AdamOptions& Options) noexcept;
};

#undef LOCTEXT_NAMESPACE
