// © 2023 Kaya Adrian.

#pragma once

#include "Macros/AtumMacrosGuards.h"
#include "Macros/AtumMacrosLog.h"

TORCH_INCLUDES_START
#include <torch/nn/options/conv.h>
TORCH_INCLUDES_END

#include "AtumLayerConvPaddingMode.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerConvPaddingMode"

/**
 * Represents the padding modes available in convolutional layers
 */
UENUM(BlueprintType, Category = "ATUM|Conv", DisplayName = "ATUM Conv Padding Mode", meta = (
	Keywords = "ATUM Conv Padding Mode"
))
enum class EAtumConvPaddingMode : uint8
{
	Zeros UMETA(DisplayName = "Zeros"), // kZeros
	Reflect UMETA(DisplayName = "Reflect"), // kReflect
	Replicate UMETA(DisplayName = "Replicate"), // kReplicate
	Circular UMETA(DisplayName = "Circular") // kCircular
};


namespace AtumEnums
{
	/**
	 * Transforms an ATUM enum value into a LibTorch enum value
	 * 
	 * @tparam Dimensions Layer's dimensionality variant
	 * @param ConvPaddingMode ATUM-equivalent padding mode
	 * @return LibTorch-equivalent padding mode
	 */
	template <uint64 Dimensions = 1ULL>
	requires (1ULL <= Dimensions && Dimensions <= 3ULL)
	UE_NODISCARD
	static typename torch::nn::ConvTransposeOptions<Dimensions>::padding_mode_t Cast(
		const EAtumConvPaddingMode ConvPaddingMode
	) noexcept
	{
		switch (ConvPaddingMode)
		{
		case EAtumConvPaddingMode::Zeros:
			return torch::kZeros;
			
		case EAtumConvPaddingMode::Reflect:
			return torch::kReflect;
			
		case EAtumConvPaddingMode::Replicate:
			return torch::kReplicate;
			
		case EAtumConvPaddingMode::Circular:
			return torch::kCircular;
			
		default:
			ATUM_LOG(Error, TEXT("Unknown ConvPaddingMode: %hhd"), ConvPaddingMode)
			return torch::kZeros;
		}
	}
	
	/**
	 * Transforms a LibTorch enum value into an ATUM enum value
	 * 
	 * @tparam Dimensions Layer's dimensionality variant
	 * @param ConvPaddingMode LibTorch-equivalent padding mode
	 * @return ATUM-equivalent padding mode
	 */
	template <uint64 Dimensions = 1ULL>
	requires (1ULL <= Dimensions && Dimensions <= 3ULL)
	UE_NODISCARD
	static EAtumConvPaddingMode Cast(
		const typename torch::nn::ConvTransposeOptions<Dimensions>::padding_mode_t ConvPaddingMode
	) noexcept
	{
		if (std::get_if<torch::enumtype::kZeros>(&ConvPaddingMode))
			return EAtumConvPaddingMode::Zeros;
		if (std::get_if<torch::enumtype::kReflect>(&ConvPaddingMode))
			return EAtumConvPaddingMode::Reflect;
		if (std::get_if<torch::enumtype::kReplicate>(&ConvPaddingMode))
			return EAtumConvPaddingMode::Replicate;
		if (std::get_if<torch::enumtype::kCircular>(&ConvPaddingMode))
			return EAtumConvPaddingMode::Circular;
		
		ATUM_LOG(Error, TEXT("Unknown ConvPaddingMode: %hs"), torch::enumtype::get_enum_name(ConvPaddingMode).c_str())
		return EAtumConvPaddingMode::Zeros;
	}
}

#undef LOCTEXT_NAMESPACE
