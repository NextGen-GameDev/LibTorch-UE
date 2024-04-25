// © 2023 Kaya Adrian.

#pragma once

#include "Layers/AtumLayerBaseOptions.h"
#include "Macros/AtumMacrosGuards.h"

TORCH_INCLUDES_START
#include <torch/nn/options/conv.h>
TORCH_INCLUDES_END

#include "AtumLayerConvTransposeOptions.generated.h"


#define LOCTEXT_NAMESPACE "AtumLayerConvTransposeOptions"

/**
 * Options structure for the Convolutional Transpose layer
 */
USTRUCT(BlueprintType, DisplayName = "ATUM Conv Transpose Layer Options")
struct ATUM_API FAtumLayerConvTransposeOptions : public FAtumLayerBaseOptions
{
	GENERATED_BODY()
	
	/**
	 * Number of channels in the input image
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	int64 InChannels;
	
	/**
	 * Number of channels in the output image
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	int64 OutChannels;
	
	/**
	 * Size of convolving kernel
	 */
	UPROPERTY(EditFixedSize, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TArray<int64> KernelSize;
	
	/**
	 * Convolution stride
	 */
	UPROPERTY(EditFixedSize, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TArray<int64> Stride;
	
	/**
	 * Padding added to all four sides of the image
	 */
	UPROPERTY(EditFixedSize, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TArray<int64> Padding;
	
	/**
	 * Padding added to one side of the output image
	 */
	UPROPERTY(EditFixedSize, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TArray<int64> OutputPadding;
	
	/**
	 * Number of blocked connections from the input to the output
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	int64 Groups;
	
	/**
	 * Determines if the output should have a learnable bias added to it
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	bool bBias;
	
	/**
	 * Spacing between kernels
	 */
	UPROPERTY(EditFixedSize, EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TArray<int64> Dilation;
	
	/**
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	explicit FAtumLayerConvTransposeOptions(uint64 Dimensions = 0ULL) noexcept;
	
	/**
	 * Returns the layer as the LibTorch object variant by overloading the relevant cast operator
	 * 
	 * @tparam Dimensions Layer's dimensionality variant
	 */
	template <uint64 Dimensions>
	requires (1ULL <= Dimensions && Dimensions <= 3ULL)
	UE_NODISCARD
	explicit operator torch::nn::ConvTransposeOptions<Dimensions>() const noexcept;
	
	/**
	 * Copies the data from a LibTorch structure
	 * 
	 * @tparam Dimensions Layer's dimensionality variant
	 * @param Options LibTorch-equivalent options instance
	 */
	template <uint64 Dimensions>
	requires (1ULL <= Dimensions && Dimensions <= 3ULL)
	void SetFrom(const torch::nn::detail::ConvNdOptions<Dimensions>& Options) noexcept;
};


template <uint64 Dimensions>
requires (1ULL <= Dimensions && Dimensions <= 3ULL)
FAtumLayerConvTransposeOptions::operator torch::nn::ConvTransposeOptions<Dimensions>() const noexcept
{
	checkf(KernelSize.Num() == Dimensions, TEXT("Kernel size must contain exactly %ull values!"), Dimensions)
	checkf(Stride.Num() == Dimensions, TEXT("Stride must contain exactly %ull values!"), Dimensions)
	checkf(Padding.Num() == Dimensions, TEXT("Padding must contain exactly %ull values!"), Dimensions)
	checkf(OutputPadding.Num() == Dimensions, TEXT("Output padding must contain exactly %ull values!"), Dimensions)
	checkf(Dilation.Num() == Dimensions, TEXT("Dilation must contain exactly %ull values!"), Dimensions)
	
	return torch::nn::ConvTransposeOptions<Dimensions>(
		InChannels,
		OutChannels,
		at::IntArrayRef(KernelSize.GetData(), Dimensions)
	).stride(at::IntArrayRef(Stride.GetData(), Dimensions))
	.padding(at::IntArrayRef(Padding.GetData(), Dimensions))
	.output_padding(at::IntArrayRef(OutputPadding.GetData(), Dimensions))
	.groups(Groups)
	.bias(bBias)
	.dilation(at::IntArrayRef(Dilation.GetData(), Dimensions))
	.padding_mode(torch::kZeros);
}

template <uint64 Dimensions>
requires (1ULL <= Dimensions && Dimensions <= 3ULL)
void FAtumLayerConvTransposeOptions::SetFrom(const torch::nn::detail::ConvNdOptions<Dimensions>& Options) noexcept
{
	checkf(KernelSize.Num() == Dimensions, TEXT("Kernel size must contain exactly %ull values!"), Dimensions)
	checkf(Stride.Num() == Dimensions, TEXT("Stride must contain exactly %ull values!"), Dimensions)
	checkf(Padding.Num() == Dimensions, TEXT("Padding must contain exactly %ull values!"), Dimensions)
	checkf(OutputPadding.Num() == Dimensions, TEXT("Output padding must contain exactly %ull values!"), Dimensions)
	checkf(Dilation.Num() == Dimensions, TEXT("Dilation must contain exactly %ull values!"), Dimensions)
	
	InChannels = Options.in_channels();
	OutChannels = Options.out_channels();
	Groups = Options.groups();
	bBias = Options.bias();
	
	for (uint64 Index = 0ULL; Index < Dimensions; ++Index)
	{
		KernelSize[Index] = Options.kernel_size()->at(Index);
		Stride[Index] = Options.stride()->at(Index);
		Padding[Index] = std::get<torch::ExpandingArray<Dimensions>>(Options.padding())->at(Index);
		OutputPadding[Index] = Options.output_padding()->at(Index);
		Dilation[Index] = Options.dilation()->at(Index);
	}
}

#undef LOCTEXT_NAMESPACE
