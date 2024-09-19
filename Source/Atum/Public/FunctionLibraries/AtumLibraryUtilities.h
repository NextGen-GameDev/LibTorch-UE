// © 2023 Kaya Adrian.

#pragma once

#include "IAtumModule.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Misc/FileHelper.h"

#include <sstream>
#include <vector>

#include "AtumLibraryUtilities.generated.h"

class UTexture2D;


#define LOCTEXT_NAMESPACE "AtumLibraryUtilities"

/**
 * Collection of Blueprint functions related to various general operations
 */
UCLASS(Abstract, Blueprintable, BlueprintType, DisplayName = "ATUM Utility Library")
class ATUM_API UAtumLibraryUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	/**
	 * Loads the content of a specific file
	 * 
	 * @param RelativePath Path to the file relative to ATUM's Content folder
	 * @param OutContent Array of text lines
	 * @return Was the file loaded successfully?
	 */
	UFUNCTION(BlueprintCallable, Category = "ATUM|Utilities")
	static FORCEINLINE bool LoadFileContentFrom(const FString& RelativePath, TArray<FString>& OutContent) noexcept
	{ return FFileHelper::LoadFileToStringArray(OutContent, *IAtumModule::GetContentDirectory(RelativePath)); }
	
	/**
	 * Change a texture's pixels
	 * 
	 * @param Texture Texture to modify
	 * @param Pixels Array of bytes
	 * @return Was the texture updated successfully?
	 */
	UFUNCTION(BlueprintCallable, Category = "ATUM|Utilities")
	static bool SetTextureData(UTexture2D* Texture, const TArray<uint8>& Pixels) noexcept;
	
	/**
	 * Generate a new texture object
	 * 
	 * @param SizeX Number of pixels on the X axis
	 * @param SizeY Number of pixels on the Y axis
	 * @param Pixels Array of pixels
	 * @return The newly-created texture
	 */
	UFUNCTION(BlueprintCallable, Category = "ATUM|Utilities")
	static UTexture2D* CreateTexture(int32 SizeX, int32 SizeY, const TArray<uint8>& Pixels) noexcept;
	
	/**
	 * Generate multiple empty textures
	 * 
	 * @param SizeX Number of pixels on the X axis
	 * @param SizeY Number of pixels on the Y axis
	 * @param OutTextures Array of generated textures
	 * @param Count Number of textures to generate
	 */
	UFUNCTION(BlueprintCallable, Category = "ATUM|Utilities")
	static void CreateEmptyTextures(
		int32 SizeX,
		int32 SizeY,
		TArray<UTexture2D*>& OutTextures,
		int32 Count = 1
	) noexcept;
	
	/**
	 * Separates a vector of values to create a readable pretty string
	 * 
	 * @tparam T Type of vector values
	 * @param Values Collection of elements to separate
	 * @param Separator String that separates the values
	 * @param Prefix String added before each element
	 * @param Suffix String added after each element
	 * @param Conjunction Final separator
	 * @param bSerialSeparator Whether to add the separator before the final element
	 * @return Pretty string made out of the vector's separated values
	 */
	template <typename T>
	[[nodiscard]]
	static std::string FormatWithConjunction(
		const std::vector<T>& Values,
		const std::string& Separator,
		const std::string& Prefix = "",
		const std::string& Suffix = "",
		const std::string& Conjunction = "",
		bool bSerialSeparator = true
	) noexcept;
};


template <typename T>
std::string UAtumLibraryUtilities::FormatWithConjunction(
	const std::vector<T>& Values,
	const std::string& Separator,
	const std::string& Prefix,
	const std::string& Suffix,
	const std::string& Conjunction,
	const bool bSerialSeparator
) noexcept
{
	const size_t ValueCount = Values.size();
	if (UNLIKELY(ValueCount == 0ULL))
		return "";
	
	std::ostringstream Stream;
	
	Stream << Prefix;
	if (ValueCount > 1ULL)
	{
		if (ValueCount > 2ULL)
		{
			std::copy(
				Values.begin(),
				Values.end() - 2,
				std::ostream_iterator<T>(Stream, (Suffix + Separator + Prefix).c_str())
			);
		}
		Stream << Values[ValueCount - 2ULL] << Suffix << (bSerialSeparator ? Separator : "") << Conjunction << Prefix;
	}
	Stream << Values.back() << Suffix;
	
	return Stream.str();
}

#undef LOCTEXT_NAMESPACE
