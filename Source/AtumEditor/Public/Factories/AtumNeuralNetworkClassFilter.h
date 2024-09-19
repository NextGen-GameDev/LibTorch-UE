// © 2023 Kaya Adrian.

#pragma once

#include "ClassViewerFilter.h"


#define LOCTEXT_NAMESPACE "AtumNeuralNetworkClassFilter"

/**
 * Neural network class filter used before creating a new asset instance
 */
class FAtumNeuralNetworkClassFilter : public IClassViewerFilter
{
	/**
	 * Collection of all classes from which an asset can be created
	 */
	TSet<const UClass*> AllowedClasses;
	
	/**
	 * Conditions that prevent a class from being used
	 */
	EClassFlags BannedClassFlags;
	
public:
	/**
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	FAtumNeuralNetworkClassFilter() noexcept;
	
	/**
	 * Checks if a class can be used to create a new asset
	 * 
	 * @param InInitOptions Options used during initialisation of the class viewer
	 * @param InClass The class to test
	 * @param InFilterFuncs Reference to collection of functions to filter the class
	 * @return Is the given class allowed?
	 */
	[[nodiscard]]
	virtual bool IsClassAllowed(
		const FClassViewerInitializationOptions& InInitOptions,
		const UClass* InClass,
		TSharedRef<FClassViewerFilterFuncs> InFilterFuncs
	) override;
	
	/**
	 * Checks if an unloaded class can be used to create a new asset
	 * 
	 * @param InInitOptions Options used during initialisation of the class viewer
	 * @param InUnloadedClassData Data of the unloaded class
	 * @param InFilterFuncs Reference to collection of functions to filter the class
	 * @return Is the given unloaded class allowed?
	 */
	[[nodiscard]]
	virtual bool IsUnloadedClassAllowed(
		const FClassViewerInitializationOptions& InInitOptions,
		TSharedRef<const IUnloadedBlueprintData> InUnloadedClassData,
		TSharedRef<FClassViewerFilterFuncs> InFilterFuncs
	) override;
	
	/**
	 * Gets every filter option from the class viewer
	 * 
	 * @param OutFilterOptions Array of references to the filter option
	 */
	virtual void GetFilterOptions(TArray<TSharedRef<FClassViewerFilterOption>>& OutFilterOptions) override;
	
	/**
	 * Getter for AllowedClasses
	 */
	[[nodiscard]]
	FORCEINLINE const TSet<const UClass*>& GetAllowedClasses() const noexcept { return AllowedClasses; }
	
	/**
	 * Setter for AllowedClasses
	 */
	[[nodiscard]]
	FORCEINLINE TSet<const UClass*>& GetAllowedClasses() noexcept { return AllowedClasses; }
	
	/**
	 * Getter for BannedClassFlags
	 */
	[[nodiscard]]
	FORCEINLINE EClassFlags GetBannedClassFlags() const noexcept { return BannedClassFlags; }
	
	/**
	 * Setter for BannedClassFlags
	 */
	[[nodiscard]]
	FORCEINLINE void SetBannedClassFlags(const EClassFlags Value) noexcept { BannedClassFlags = Value; }
};

#undef LOCTEXT_NAMESPACE
