// © 2023 Kaya Adrian.

#pragma once

#include "Factories/Factory.h"

#include "AtumNeuralNetworkFactory.generated.h"

class UAtumNeuralNetwork;


#define LOCTEXT_NAMESPACE "AtumNeuralNetworkFactory"

/**
 * Factory object responsible for creating new neural network assets in editor
 */
UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Neural Network Factory")
class ATUMEDITOR_API UAtumNeuralNetworkFactory : public UFactory
{
	GENERATED_BODY()
	
	/**
	 * Base class allowed to create new neural networks from
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TSubclassOf<UAtumNeuralNetwork> NeuralNetworkClass;
	
public:
	/**
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	UAtumNeuralNetworkFactory() noexcept;
	
	/**
	 * Creates a new neural network asset
	 * 
	 * @param InClass Base class of the neural network
	 * @param InParent Object owning the network
	 * @param InName Name of the network
	 * @param Flags Conditions to apply to the network
	 * @param Context Object containing additional information for debugging purposes
	 * @param Warn Controls how warnings should be dealt with if an issue was encountered
	 * @return 
	 */
	[[nodiscard]]
	virtual UObject* FactoryCreateNew(
		UClass* InClass,
		UObject* InParent,
		FName InName,
		EObjectFlags Flags,
		UObject* Context,
		FFeedbackContext* Warn
	) override;
	
	/**
	 * Controls how the class dialog picker should behave
	 * 
	 * @return Was a class selected?
	 */
	virtual bool ConfigureProperties() override;
	
	/**
	 * Getter for NeuralNetworkClass
	 */
	[[nodiscard]]
	FORCEINLINE TSubclassOf<UAtumNeuralNetwork> GetNeuralNetworkClass() const noexcept { return NeuralNetworkClass; }
	
	/**
	 * Setter for NeuralNetworkClass
	 */
	[[nodiscard]]
	FORCEINLINE void SetNeuralNetworkClass(const TSubclassOf<UAtumNeuralNetwork> Value) noexcept
	{ NeuralNetworkClass = Value; }
};

#undef LOCTEXT_NAMESPACE
