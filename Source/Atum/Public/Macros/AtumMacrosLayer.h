// © 2023 Kaya Adrian.

#pragma once


#define LOCTEXT_NAMESPACE "AtumMacrosLayer"

/**
 * Macro which adds boilerplate code related to a layer's options
 * 
 * @param OptionsClass Layer's options type
 */
#define GENERATED_ATUM_LAYER_OPTIONS_ONLY(OptionsClass) \
protected: \
	/**
	 * Loads the layer data from a file
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
	virtual const FAtumLayerBaseOptions* GetBaseLayerOptions() const noexcept override { return &Options; } \
	\
	/**
	 * Getter for Options as its base class
	 */ \
	[[nodiscard]] \
	virtual FAtumLayerBaseOptions* GetBaseLayerOptions() noexcept override { return &Options; } \
	\
	/**
	 * Getter for Options
	 */ \
	[[nodiscard]] \
	FORCEINLINE const OptionsClass& GetLayerOptions() const noexcept { return Options; } \
	\
	/**
	 * Getter for Options
	 */ \
	[[nodiscard]] \
	FORCEINLINE OptionsClass& GetLayerOptions() noexcept { return Options; } \
	\
private:

/**
 * Macro which adds boilerplate code related to a layer's LibTorch module
 * 
 * @param ModuleClass Type of layer module
 */
#define GENERATED_ATUM_LAYER_MODULE_ONLY(ModuleClass) \
GENERATED_ATUM_LAYER_MODULE_ONLY_IMPL(ModuleClass, ModuleClass##Impl)

/**
 * Macro which adds boilerplate code related to a layer's LibTorch module
 * 
 * @param ModuleClass Type of layer module
 * @param ModuleClassImpl Implementation of the layer module
 */
#define GENERATED_ATUM_LAYER_MODULE_ONLY_IMPL(ModuleClass, ModuleClassImpl) \
protected: \
	/**
	 * Pointer to LibTorch module object
	 */ \
	TSharedPtr<ModuleClass> Module = nullptr; \
	\
	/**
	 * Function that runs when IAtumLayer::InitializeData is called
	 * 
	 * @param bRetry Should initialisation be done again?
	 * @return Is the layer initialised?
	 */ \
	virtual bool OnInitializeData_Implementation(bool bRetry = true) override; \
	\
	/**
	 * Function that runs when IAtumLayer::Forward is called
	 * 
	 * @param Input Tensor to operate on
	 * @param Output The resulting tensor
	 * @return Did the layer forward successfully?
	 */ \
	virtual bool OnForward_Implementation( \
		const TScriptInterface<IAtumTensor>& Input, \
		TScriptInterface<IAtumTensor>& Output \
	) override; \
	\
	/**
	 * Sets the layer's module using a base module
	 * 
	 * @param Value Pointer to base module
	 */ \
	virtual void SetBaseModule(const torch::nn::Module* const Value) noexcept override \
	{ \
		Module = Value ? MakeShareable(new ModuleClass(std::make_shared<ModuleClassImpl>( \
			*dynamic_cast<const ModuleClassImpl*>(Value) \
		))) : nullptr; \
	} \
	\
public: \
	/**
	 * Getter for Module as its base class
	 */ \
	[[nodiscard]] \
	virtual const torch::nn::Module* GetBaseModule() const noexcept override \
	{ return Module ? Module->get() : nullptr; } \
	\
	/**
	 * Getter for Module
	 */ \
	[[nodiscard]] \
	FORCEINLINE TSharedPtr<const ModuleClass> GetModule() const noexcept { return Module; } \
	\
	/**
	 * Getter for Module
	 */ \
	[[nodiscard]] \
	FORCEINLINE TSharedPtr<ModuleClass> GetModule() noexcept { return Module; } \
	\
private:

/**
 * Macro which adds boilerplate code related to a layer's options and LibTorch module
 *
 * @param OptionsClass Layer's options type
 * @param ModuleClass Type of layer module
 */
#define GENERATED_ATUM_LAYER(OptionsClass, ModuleClass) \
GENERATED_ATUM_LAYER_IMPL(OptionsClass, ModuleClass, ModuleClass##Impl)

/**
 * Macro which adds boilerplate code related to a layer's options and LibTorch module
 *
 * @param OptionsClass Layer's options type
 * @param ModuleClass Type of layer module
 * @param ModuleClassImpl Implementation of the layer module
 */
#define GENERATED_ATUM_LAYER_IMPL(OptionsClass, ModuleClass, ModuleClassImpl) \
	GENERATED_ATUM_LAYER_OPTIONS_ONLY(OptionsClass) \
	GENERATED_ATUM_LAYER_MODULE_ONLY_IMPL(ModuleClass, ModuleClassImpl) \
private:

#undef LOCTEXT_NAMESPACE
