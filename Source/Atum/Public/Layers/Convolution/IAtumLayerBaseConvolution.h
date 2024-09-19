// © 2023 Kaya Adrian.

#pragma once

#include "Layers/IAtumLayer.h"

#include "IAtumLayerBaseConvolution.generated.h"


#define LOCTEXT_NAMESPACE "IAtumLayerBaseConvolution"

/**
 * Interface object class used by the engine
 */
UINTERFACE(MinimalAPI, Blueprintable, BlueprintType, DisplayName = "ATUM Convolution Layer Base")
class UAtumLayerBaseConvolution : public UAtumLayer
{
	GENERATED_BODY()
};

/**
 * Convolution layer interface for creating deep learning operations
 */
class ATUM_API IAtumLayerBaseConvolution : public IAtumLayer
{
	GENERATED_BODY()
	
protected:
	/**
	 * Checks if the channel sizes are divisible by the group size
	 * 
	 * @param InChannels Input channel count
	 * @param OutChannels Output channel count
	 * @param Groups Number of groups
	 * @return Can both channel counts be divisible by the group count?
	 */
	[[nodiscard]]
	static bool AreChannelsDivisibleByGroups(int64 InChannels, int64 OutChannels, int64 Groups) noexcept;
	
	/**
	 * Checks if the input sizes are greater than 0
	 * 
	 * @param Sizes Given input sizes
	 * @param Name Layer object name
	 * @param bAllowZero Determines if 0 should be ignored
	 * @return Are the sizes positive?
	 */
	[[nodiscard]]
	bool AreSizesPositive(const TArray<int64>& Sizes, const FString& Name, bool bAllowZero = false) const noexcept;
};

#undef LOCTEXT_NAMESPACE
