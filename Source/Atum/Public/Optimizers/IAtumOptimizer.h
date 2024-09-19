// © 2023 Kaya Adrian.

#pragma once

#include "Serializable/IAtumSerializable.h"

#include "IAtumOptimizer.generated.h"

class IAtumTensor;
struct FAtumOptimizerBaseOptions;

// ReSharper disable CppUE4CodingStandardNamingViolationWarning
namespace torch::optim
{
	class Optimizer;
}
// ReSharper restore CppUE4CodingStandardNamingViolationWarning


#define LOCTEXT_NAMESPACE "IAtumOptimizer"

DECLARE_DYNAMIC_DELEGATE_OneParam(FAtumOptimizerLossClosure, const TScriptInterface<IAtumTensor>&, Loss);


/**
 * Structure which deals with deleting the optimiser's parameters
 */
struct FOptimizerParametersDeleter
{
	/**
	 * Removes every optimiser parameter as soon as the pointer is deleted
	 * 
	 * @param Optimizer Pointer to the optimiser to clean
	 */
	void operator()(torch::optim::Optimizer* Optimizer) const noexcept;
};


/**
 * Interface object class used by the engine
 */
UINTERFACE(MinimalAPI, Blueprintable, BlueprintType, DisplayName = "ATUM Optimizer")
class UAtumOptimizer : public UAtumSerializable
{
	GENERATED_BODY()
};

/**
 * Optimiser interface that can be used to implement optimisers for deep learning
 */
class ATUM_API IAtumOptimizer : public IAtumSerializable
{
	GENERATED_BODY()
	
protected:
	/**
	 * Used to check if the optimiser has already been initialised or not
	 */
	bool bInitialized;
	
	/**
	 * Pointer to LibTorch optimiser object
	 */
	TSharedPtr<torch::optim::Optimizer> Optimizer;
	
public:
	/**
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	IAtumOptimizer() noexcept;
	
	/**
	 * Initialises the optimiser based on its options only once
	 * 
	 * @param bRetry Should initialisation be done again?
	 * @return Is the optimiser initialised?
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Optimizer", meta = (
		AutoCreateRefTerm = "Parameters"
	))
	bool InitializeData(bool bRetry = true);
	
	/**
	 * Sets the optimiser's gradient to zero
	 * 
	 * @param bSetToNone Should the gradients be set to none instead?
	 * @return Was the operation successful?
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Layer")
	bool SetGradientToZero(bool bSetToNone = true);
	
	/**
	 * Gets this optimiser's current parameters
	 * 
	 * @param OutParameters Array of all parameters
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Optimizer")
	void GetParameters(TArray<TScriptInterface<IAtumTensor>>& OutParameters) const;
	
	/**
	 * Sets this optimiser's parameters
	 * 
	 * @param Parameters Array of new parameters
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Optimizer")
	void SetParameters(const TArray<TScriptInterface<IAtumTensor>>& Parameters);
	
	/**
	 * Updates the parameters one time
	 * 
	 * @param Class Type of tensor implementation to use
	 */
	void Step(const UClass* Class) noexcept;
	
	/**
	 * Updates the parameters one time
	 * 
	 * @param Class Type of tensor implementation to use
	 * @param OutLoss Computed loss value
	 * @param LossClosure Function that clears the gradients and computes the loss
	 */
	FORCEINLINE void Step(
		const UClass* Class,
		TScriptInterface<IAtumTensor>& OutLoss,
		const FAtumOptimizerLossClosure& LossClosure = FAtumOptimizerLossClosure()
	) noexcept
	{ Execute_K2_Step(_getUObject(), Class, OutLoss, LossClosure); }
	
	/**
	 * Getter for Options as its base class
	 */
	[[nodiscard]]
	virtual const FAtumOptimizerBaseOptions* GetBaseOptimizerOptions() const noexcept;
	
	/**
	 * Getter for Options as its base class
	 */
	[[nodiscard]]
	virtual FAtumOptimizerBaseOptions* GetBaseOptimizerOptions() noexcept;
	
protected:
	/**
	 * Function that runs when IAtumOptimizer::InitializeData is called
	 * 
	 * @param bRetry Should initialisation be done again?
	 * @return Is the optimiser initialised?
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Optimizer", meta = (
		AutoCreateRefTerm = "Parameters"
	))
	bool OnInitializeData(bool bRetry = true);
	
	/**
	 * Blueprint function to call IAtumOptimizer::Step
	 * 
	 * @param Class Type of tensor implementation to use
	 * @param OutLoss Computed loss value
	 * @param LossClosure Function that clears the gradients and computes the loss
	 */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ATUM|Optimizer", DisplayName = "Step", meta = (
		AdvancedDisplay = "2",
		AutoCreateRefTerm = "LossClosure"
	))
	void K2_Step(
		UPARAM(meta = (MustImplement = "/Script/Atum.AtumTensor")) const UClass* Class,
		TScriptInterface<IAtumTensor>& OutLoss,
		const FAtumOptimizerLossClosure& LossClosure
	);
	
	/**
	 * Function that runs when IAtumOptimizer::InitializeData is called
	 * 
	 * @param bRetry Should initialisation be done again?
	 * @return Is the optimiser initialised?
	 */
	virtual bool OnInitializeData_Implementation(bool bRetry = true);
	
	/**
	 * Sets the optimiser's gradient to zero
	 * 
	 * @param bSetToNone Should the gradients be set to none instead?
	 * @return Was the operation successful?
	 */
	virtual bool SetGradientToZero_Implementation(bool bSetToNone = true) noexcept;
	
	/**
	 * Blueprint function to call IAtumOptimizer::Step
	 * 
	 * @param Class Type of tensor implementation to use
	 * @param OutLoss Computed loss value
	 * @param LossClosure Function that clears the gradients and computes the loss
	 */
	virtual void K2_Step_Implementation(
		const UClass* Class,
		TScriptInterface<IAtumTensor>& OutLoss,
		const FAtumOptimizerLossClosure& LossClosure
	) noexcept;
	
	/**
	 * Gets this optimiser's current parameters
	 * 
	 * @param OutParameters Array of all parameters
	 */
	virtual void GetParameters_Implementation(TArray<TScriptInterface<IAtumTensor>>& OutParameters) const noexcept;
	
	/**
	 * Sets this optimiser's parameters
	 * 
	 * @param Parameters Array of new parameters
	 */
	virtual void SetParameters_Implementation(const TArray<TScriptInterface<IAtumTensor>>& Parameters) noexcept;
	
	/**
	 * Saves the optimiser data to a file
	 * 
	 * @param RelativePath Path to file relative to ATUM's Content folder
	 * @return Was the operation successful?
	 */
	virtual bool SaveToFile_Implementation(const FString& RelativePath) const override;
	
	/**
	 * Loads the optimiser data from a file
	 * 
	 * @param RelativePath Path to file relative to ATUM's Content folder
	 * @return Was the operation successful?
	 */
	virtual bool LoadFromFile_Implementation(const FString& RelativePath) override;
	
private:
	/**
	 * Initialises the optimiser based on its options only once
	 * 
	 * @param bRetry Should initialisation be done again?
	 * @return Is the optimiser initialised?
	 */
	bool InitializeData_Implementation(bool bRetry = true) noexcept;
	
public:
	/**
	 * Getter for bInitialized
	 */
	[[nodiscard]]
	FORCEINLINE bool IsInitialized() const noexcept { return bInitialized; }
	
	/**
	 * Getter for Optimizer
	 */
	[[nodiscard]]
	FORCEINLINE TSharedPtr<const torch::optim::Optimizer> GetOptimizer() const noexcept { return Optimizer; }
	
	/**
	 * Getter for Optimizer
	 */
	[[nodiscard]]
	FORCEINLINE TSharedPtr<torch::optim::Optimizer> GetOptimizer() noexcept { return Optimizer; }
};

#undef LOCTEXT_NAMESPACE
