// © 2023 Kaya Adrian.

#pragma once


#define LOCTEXT_NAMESPACE "AtumMacrosOptimizer"

/**
 * Macro which adds boilerplate code related to an optimiser's options
 * 
 * @param OptionsClass Optimiser's options type
 */
#define GENERATED_ATUM_OPTIMIZER(OptionsClass) \
protected: \
	/**
	 * Function that runs when IAtumOptimizer::InitializeData is called
	 * 
	 * @param bRetry Should initialisation be done again?
	 * @return Is the optimiser initialised?
	 */ \
	virtual bool OnInitializeData_Implementation(bool bRetry = true) override; \
	\
	/**
	 * Loads the optimiser data from a file
	 * 
	 * @param RelativePath Path to file relative to ATUM's Content folder
	 * @return Was the operation successful?
	 */ \
	virtual bool LoadFromFile_Implementation(const FString& RelativePath) override; \
	\
public: \
	/**
	 * Getter for Options as its base class
	 */ \
	[[nodiscard]] \
	virtual const FAtumOptimizerBaseOptions* GetBaseOptimizerOptions() const noexcept override { return &Options; } \
	\
	/**
	 * Getter for Options as its base class
	 */ \
	[[nodiscard]] \
	virtual FAtumOptimizerBaseOptions* GetBaseOptimizerOptions() noexcept override { return &Options; } \
	\
	/**
	 * Getter for Options
	 */ \
	[[nodiscard]] \
	FORCEINLINE const OptionsClass& GetOptimizerOptions() const noexcept { return Options; } \
	\
	/**
	 * Getter for Options
	 */ \
	[[nodiscard]] \
	FORCEINLINE OptionsClass& GetOptimizerOptions() noexcept { return Options; } \
	\
private:

#undef LOCTEXT_NAMESPACE
