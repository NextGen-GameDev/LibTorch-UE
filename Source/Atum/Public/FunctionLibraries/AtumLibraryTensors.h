// © 2023 Kaya Adrian.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Tensors/IAtumTensor.h"

#include "AtumLibraryTensors.generated.h"

class UProperty;


#define LOCTEXT_NAMESPACE "AtumLibraryTensors"

/**
 * Collection of Blueprint functions related to tensors
 */
UCLASS(Abstract, Blueprintable, BlueprintType, DisplayName = "ATUM Tensor Library")
class ATUM_API UAtumLibraryTensors : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	/**
	 * Blueprint function to call UAtumLibraryTensors::GenericArray_Serialize
	 * 
	 * @param Target Array property
	 * @param OutBytes The serialised array
	 */
	UFUNCTION(BlueprintCallable, Category = "ATUM|Cast", DisplayName = "Serialize Array", CustomThunk, meta = (
		ArrayParm = "Target",
		CompactNodeTitle = "Serialize",
		Keywords = "ATUM Cast Serialise Serialize Target Any Wildcard Array Out Bytes"
	))
	static void K2_SerializeArray(const TArray<UProperty*>& Target, TArray<uint8>& OutBytes);
	
	/**
	 * Blueprint function to call UAtumLibraryTensors::GenericArray_Deserialize
	 * 
	 * @param Bytes The serialised array
	 * @param TargetTypeProvider Array that provides the output type
	 * @param OutTarget Array property
	 */
	UFUNCTION(BlueprintCallable, Category = "ATUM|Cast", DisplayName = "Deserialize Array", CustomThunk, meta = (
		ArrayParm = "TargetTypeProvider",
		ArrayTypeDependentParams = "OutTarget",
		CompactNodeTitle = "Deserialize",
		Keywords = "ATUM Cast Deserialise Deserialize Any Wildcard Bytes Target Type Provider Out"
	))
	static void K2_DeserializeArray(
		const TArray<uint8>& Bytes,
		const TArray<UProperty*>& TargetTypeProvider,
		TArray<UProperty*>& OutTarget
	);
	
	/**
	 * Blueprint function to call IAtumTensor::GetDefaultDeviceType
	 * 
	 * @return The device on which tensors are created by default
	 */
	[[nodiscard]]
	UFUNCTION(BlueprintPure, Category = "ATUM|Tensor", DisplayName = "Get Default Device Type", meta = (
		Keywords = "ATUM Tensor Get Default Device Type"
	))
	static FORCEINLINE EAtumTensorDeviceType K2_GetDefaultDeviceType() noexcept
	{ return IAtumTensor::GetDefaultDeviceType(); }
	
	/**
	 * Blueprint function to call IAtumTensor::SetDefaultDeviceType
	 * 
	 * @param Value New default device
	 */
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor", DisplayName = "Set Default Device Type", meta = (
		Keywords = "ATUM Tensor Set Default Device Type Value"
	))
	static FORCEINLINE void K2_SetDefaultDeviceType(const EAtumTensorDeviceType Value) noexcept
	{ IAtumTensor::SetDefaultDeviceType(Value); }
	
	/**
	 * Gets the LibTorch device on which tensors are created by default
	 * 
	 * @return The LibTorch default device type
	 */
	[[nodiscard]]
	static FORCEINLINE c10::DeviceType GetDefaultTorchDeviceType() noexcept
	{ return AtumEnums::Cast(K2_GetDefaultDeviceType()); }
	
	/**
	 * Sets the LibTorch device on which tensors are created by default
	 * 
	 * @param Value New LibTorch default device
	 */
	static FORCEINLINE void SetDefaultTorchDeviceType(const c10::DeviceType Value) noexcept
	{ K2_SetDefaultDeviceType(AtumEnums::Cast(Value)); }
	
public:
	/**
	 * Creates a new empty tensor
	 * 
	 * @param Class Type of tensor implementation
	 * @param Sizes Array of sizes
	 * @return The created tensor
	 */
	[[nodiscard]]
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor|Constructor", DisplayName = "Make Empty Tensor", meta = (
		AutoCreateRefTerm = "Sizes",
		DeterminesOutputType = "Class",
		CompactNodeTitle = "Empty Tensor",
		Keywords = "ATUM Constructor Make Empty Tensor Class Sizes"
	))
	static UObject* Empty(
		UPARAM(meta = (MustImplement = "/Script/Atum.AtumTensor")) const UClass* Class,
		const TArray<int64>& Sizes
	);
	
	/**
	 * Creates a new eye tensor
	 * 
	 * @param Class Type of tensor implementation
	 * @param Size Square matrix size
	 * @return The created tensor
	 */
	UE_NODISCARD_CTOR
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor|Constructor", DisplayName = "Make Eye Tensor", meta = (
		DeterminesOutputType = "Class",
		CompactNodeTitle = "Eye Tensor",
		Keywords = "ATUM Constructor Make Eye Tensor Class Size"
	))
	static UObject* Eye(
		UPARAM(meta = (MustImplement = "/Script/Atum.AtumTensor")) const UClass* Class,
		int64 Size = 0LL
	);
	
	/**
	 * Creates a new zero-filled tensor
	 * 
	 * @param Class Type of tensor implementation
	 * @param Sizes Array of sizes
	 * @return The created tensor
	 */
	[[nodiscard]]
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor|Constructor", DisplayName = "Make Zeros Tensor", meta = (
		AutoCreateRefTerm = "Sizes",
		DeterminesOutputType = "Class",
		CompactNodeTitle = "Zeros Tensor",
		Keywords = "ATUM Constructor Make Zeros Tensor Class Sizes"
	))
	static UObject* Zeros(
		UPARAM(meta = (MustImplement = "/Script/Atum.AtumTensor")) const UClass* Class,
		const TArray<int64>& Sizes
	);
	
	/**
	 * Creates a new one-filled tensor
	 * 
	 * @param Class Type of tensor implementation
	 * @param Sizes Array of sizes
	 * @return The created tensor
	 */
	[[nodiscard]]
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor|Constructor", DisplayName = "Make Ones Tensor", meta = (
		AutoCreateRefTerm = "Sizes",
		DeterminesOutputType = "Class",
		CompactNodeTitle = "Ones Tensor",
		Keywords = "ATUM Constructor Make Ones Tensor Class Sizes"
	))
	static UObject* Ones(
		UPARAM(meta = (MustImplement = "/Script/Atum.AtumTensor")) const UClass* Class,
		const TArray<int64>& Sizes
	);
	
	/**
	 * Creates a new random tensor
	 * 
	 * @param Class Type of tensor implementation
	 * @param Sizes Array of sizes
	 * @return The created tensor
	 */
	[[nodiscard]]
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor|Constructor", DisplayName = "Make Random Tensor", meta = (
		AutoCreateRefTerm = "Sizes",
		DeterminesOutputType = "Class",
		CompactNodeTitle = "Random Tensor",
		Keywords = "ATUM Constructor Make Random Tensor Class Sizes"
	))
	static UObject* Random(
		UPARAM(meta = (MustImplement = "/Script/Atum.AtumTensor")) const UClass* Class,
		const TArray<int64>& Sizes
	);
	
	/**
	 * Creates a new normally-distributed random tensor
	 * 
	 * @param Class Type of tensor implementation
	 * @param Sizes Array of sizes
	 * @param DeviceType Device on which the tensor is created
	 * @return The created tensor
	 */
	[[nodiscard]]
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor|Constructor", DisplayName = "Make RandN Tensor", meta = (
		AutoCreateRefTerm = "Sizes",
		DeterminesOutputType = "Class",
		CompactNodeTitle = "RandN Tensor",
		Keywords = "ATUM Constructor Make Normally Distributed Random Tensor Class Sizes Device Type"
	))
	static UObject* RandN(
		UPARAM(meta = (MustImplement = "/Script/Atum.AtumTensor")) const UClass* Class,
		const TArray<int64>& Sizes,
		EAtumTensorDeviceType DeviceType = EAtumTensorDeviceType::Cpu
	);
	
	/**
	 * Blueprint function to call IAtumTensor::ToString
	 * 
	 * @param Tensor Generic tensor object
	 * @return The tensor as a string
	 */
	[[nodiscard]]
	UFUNCTION(BlueprintPure, Category = "ATUM|Cast", DisplayName = "Tensor To String", CustomThunk, meta = (
		BlueprintAutocast,
		CompactNodeTitle = "->",
		Keywords = "ATUM Cast Tensor To String"
	))
	static FORCEINLINE FString Conv_TensorToString(const TScriptInterface<const IAtumTensor>& Tensor) noexcept
	{ return Tensor ? Tensor->ToString() : TEXT(""); }
	
	/**
	 * Blueprint function to call IAtumTensor::Add
	 * 
	 * @param Left First tensor
	 * @param Right Second tensor
	 * @param Class Type of tensor implementation for the result
	 * @return The sum of the two tensors
	 */
	[[nodiscard]]
	UFUNCTION(BlueprintPure, Category = "ATUM|Operator", DisplayName = "Add Tensors", meta = (
		CompactNodeTitle = "+",
		Keywords = "ATUM Operator Overload + Add Plus Tensor Left Right Class"
	))
	static TScriptInterface<IAtumTensor> Add_TensorTensor(
		const TScriptInterface<IAtumTensor>& Left,
		const TScriptInterface<IAtumTensor>& Right,
		UPARAM(meta = (MustImplement = "/Script/Atum.AtumTensor")) const UClass* const Class
	) noexcept
	{ return Left->Add(Right, Class); }
	
	/**
	 * Performs the binary cross entropy algorithm
	 * 
	 * @param Output Generated data
	 * @param Label Ground truth
	 * @param Class Type of tensor implementation of the result
	 * @return The loss
	 */
	[[nodiscard]]
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor", meta = (
		Keywords = "ATUM Tensor Binary Cross Entropy Output Label Class"
	))
	static TScriptInterface<IAtumTensor> BinaryCrossEntropy(
		const TScriptInterface<IAtumTensor>& Output,
		const TScriptInterface<IAtumTensor>& Label,
		UPARAM(meta = (MustImplement = "/Script/Atum.AtumTensor")) const UClass* Class
	) noexcept;

	/**
	 * Performs the mean square error algorithm
	 * 
	 * @param Output Generated data
	 * @param Label Ground truth
	 * @param Class Type of tensor implementation of the result
	 * @return The loss
	 */
	[[nodiscard]]
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor", meta = (
		Keywords = "ATUM Tensor Mean Square Error Output Label Class"
	))
	static TScriptInterface<IAtumTensor> MeanSquareError(
		const TScriptInterface<IAtumTensor>& Output,
		const TScriptInterface<IAtumTensor>& Label,
			

		UPARAM(meta = (MustImplement = "/Script/Atum.AtumTensor")) const UClass* Class
	) noexcept;
		
	
	/**
	 * Serialises an array of any type
	 * 
	 * @param TargetAddress Array address
	 * @param TargetProperty Pointer to the array property
	 * @param OutBytes The serialised array
	 */
	static void GenericArray_Serialize(
		const uint8* TargetAddress,
		const FArrayProperty* TargetProperty,
		TArray<uint8>& OutBytes
	) noexcept;
	
	/**
	 * Deserialises an array of any type
	 * 
	 * @param Bytes The serialised array
	 * @param OutTargetAddress Array address
	 * @param OutTargetProperty Pointer to the array property
	 */
	static void GenericArray_Deserialize(
		const TArray<uint8>& Bytes,
		uint8* OutTargetAddress,
		const FArrayProperty* OutTargetProperty
	) noexcept;
	
private:
	DECLARE_FUNCTION(execK2_SerializeArray) noexcept;
	DECLARE_FUNCTION(execK2_DeserializeArray) noexcept;
	DECLARE_FUNCTION(execConv_TensorToString) noexcept;
};

#undef LOCTEXT_NAMESPACE
