// © 2023 Kaya Adrian.

#pragma once

#include "AtumSettingsBase.h"

#include "AtumSettingsDev.generated.h"


#define LOCTEXT_NAMESPACE "AtumSettingsDev"

/**
 * ATUM settings for development purposes
 */
UCLASS(MinimalAPI, BlueprintType, DisplayName = "ATUM Dev Settings")
class UAtumSettingsDev : public UAtumSettingsBase
{
	GENERATED_BODY()
	
protected:
	/**
	 * Controls if the ATUM runtime module can output logs to the console
	 */
	UPROPERTY(Config, EditAnywhere, BlueprintReadWrite, DisplayName = "Enable LogAtum", meta = (
		AllowPrivateAccess,
		ConsoleVariable = "atum.Dev.EnableLogAtum"
	))
	bool bLogAtumEnabled;
	
public:
	/**
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	UAtumSettingsDev() noexcept;
	
#if WITH_EDITOR
	/**
	 * Gets the section name of these settings
	 * 
	 * @return Localisable section text
	 */
	[[nodiscard]]
	virtual FText GetSectionText() const override;
	
	/**
	 * Gets the description of the section
	 * 
	 * @return Localisable section description
	 */
	[[nodiscard]]
	virtual FText GetSectionDescription() const override;
#endif
	
	/**
	 * Getter for bLogAtumEnabled
	 */
	[[nodiscard]]
	FORCEINLINE bool IsLogAtumEnabled() const noexcept { return bLogAtumEnabled; }
	
	/**
	 * Setter for bLogAtumEnabled
	 */
	[[nodiscard]]
	FORCEINLINE void SetLogAtumEnabled(const bool bValue) noexcept { bLogAtumEnabled = bValue; }
};

#undef LOCTEXT_NAMESPACE
