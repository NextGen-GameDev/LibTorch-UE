// © 2023 Kaya Adrian.

#pragma once

#include "Layers/AtumLayerBaseOptions.h"

#include "AtumNeuralNetworkOptions.generated.h"

class UAtumNeuralNetworkLayers;


#define LOCTEXT_NAMESPACE "AtumNeuralNetworkOptions"

// ReSharper disable CppUE4CodingStandardNamingViolationWarning
namespace torch::nn
{
	struct AtumNetworkOptions
	{
	};
}
// ReSharper restore CppUE4CodingStandardNamingViolationWarning


/**
 * Options structure for the neural network
 */
USTRUCT(BlueprintType, DisplayName = "ATUM Neural Network Options")
struct ATUM_API FAtumNeuralNetworkOptions : public FAtumLayerBaseOptions
{
	GENERATED_BODY()
	
	/**
	 * Pointer to object holding the network's layer data
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TObjectPtr<UAtumNeuralNetworkLayers> LayersData;
	
	/**
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	FAtumNeuralNetworkOptions() noexcept;
	
	/**
	 * Returns the layer as the LibTorch object variant by overloading the relevant cast operator
	 */
	[[nodiscard]]
	FORCEINLINE explicit operator torch::nn::AtumNetworkOptions() const noexcept
	{ return torch::nn::AtumNetworkOptions(); }
};

#undef LOCTEXT_NAMESPACE
