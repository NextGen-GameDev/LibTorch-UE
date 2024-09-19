// © 2023 Kaya Adrian.

#pragma once

#include "AtumTensorDeviceType.h"
#include "AtumTensorRetainGraphMode.h"
#include "AtumTensorScalarType.h"
#include "Serializable/IAtumSerializable.h"

TORCH_INCLUDES_START
#include <torch/csrc/autograd/generated/variable_factories.h>
TORCH_INCLUDES_END

#include "IAtumTensor.generated.h"


#define LOCTEXT_NAMESPACE "IAtumTensor"

/**
 * Interface object class used by the engine
 */
UINTERFACE(MinimalAPI, NotBlueprintable, BlueprintType, DisplayName = "ATUM Tensor")
class UAtumTensor : public UAtumSerializable
{
	GENERATED_BODY()
};

/**
 * Multi-dimensional array interface meant to be used in linear algebra problems
 */
class ATUM_API IAtumTensor : public IAtumSerializable
{
	GENERATED_BODY()
	
protected:
	/**
	 * Device on which all tensors will be created by default
	 */
	static EAtumTensorDeviceType DefaultDeviceType;
	
	/**
	 * Pointer to LibTorch tensor object
	 */
	TUniquePtr<at::Tensor> Data;
	
	/**
	 * Type of scalar which represents the inner values
	 */
	EAtumTensorScalarType ScalarType;
	
public:
	/**
	 * Constructor
	 */
	UE_NODISCARD_CTOR
	IAtumTensor() noexcept;
	
	/**
	 * Checks if the tensor object can be used
	 * 
	 * @return Is the tensor defined?
	 */
	[[nodiscard]]
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor")
	virtual bool IsDefined() const noexcept;
	
	/**
	 * Checks if it's possible to perform operations between two tensors
	 * 
	 * @param BroadcastTensor Tensor to test broadcasting
	 * @return Are the two tensors broadcastable with each other?
	 */
	[[nodiscard]]
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor", DisplayName = "Is Broadcastable With")
	virtual bool IsBroadcastableWith(const TScriptInterface<IAtumTensor>& BroadcastTensor) const noexcept;
	
	/**
	 * Changes the first tensor's shape in order to be broadcastable with the second
	 * 
	 * @param BroadcastTensor Tensor to broadcast to
	 * @return Was the broadcast successful?
	 */
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor", DisplayName = "Broadcast To")
	virtual bool BroadcastTo(const TScriptInterface<IAtumTensor>& BroadcastTensor) noexcept;
	
	/**
	 * Removes the tensor from the global gradient graph
	 * @param OutDetachedTensor The original tensor, but detached
	 */
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor")
	virtual void Detach(TScriptInterface<IAtumTensor>& OutDetachedTensor) const noexcept;
	
	/**
	 * Gets the current gradient
	 * 
	 * @param OutGradient Tensor's gradient as another tensor
	 */
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor")
	virtual void GetGradient(TScriptInterface<IAtumTensor>& OutGradient) const noexcept;
	
	/**
	 * Checks if the tensor's gradient is necessary
	 * 
	 * @return Must the gradient of this tensor be computed?
	 */
	[[nodiscard]]
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor")
	virtual bool DoesRequireGradient() const noexcept;
	
	/**
	 * Sets whether or not the gradient is required
	 * 
	 * @param bValue Is the gradient required?
	 * @return The tensor itself
	 */
	virtual IAtumTensor* SetRequireGradient(bool bValue) noexcept;
	
	/**
	 * Gets this tensor's sizes
	 * 
	 * @param OutSizes Array of sizes
	 */
	[[nodiscard]]
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor")
	virtual void GetSizes(TArray<int64>& OutSizes) const noexcept;
	
	/**
	 * Gets the device on which this tensor sits
	 * 
	 * @return This tensor's device type
	 */
	[[nodiscard]]
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor")
	virtual EAtumTensorDeviceType GetDeviceType() const noexcept;
	
	/**
	 * Moves the tensor to another device
	 * 
	 * @param Value Device
	 */
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor")
	virtual void SetDeviceType(EAtumTensorDeviceType Value) noexcept;
	
	/**
	 * Gets the type of value this tensor holds
	 * 
	 * @return This tensor's scalar type
	 */
	[[nodiscard]]
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor")
	virtual EAtumTensorScalarType GetScalarType() const noexcept;

	/**
	 * Sets the type of value this tensor holds
	 *
	 * @param Value Scalar type
	 */
	[[nodiscard]]
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor")
	virtual void SetScalarType(EAtumTensorScalarType Value) noexcept;
	
	/**
	 * Gets how many scalar values are being held in the tensor
	 * 
	 * @return Number of elements
	 */
	[[nodiscard]]
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor")
	virtual int64 GetElementCount() const noexcept;
	
	/**
	 * Gets how much memory is being occupied by one element
	 * 
	 * @return An element's size
	 */
	[[nodiscard]]
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor")
	virtual int64 GetElementSize() const noexcept;
	
	/**
	 * Gets the tensor's values in the form of raw bytes
	 * 
	 * @param OutValues Array of values as bytes
	 * @param OutSizes Array of sizes
	 */
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor")
	virtual void GetSerializedValues(TArray<uint8>& OutValues, TArray<int64>& OutSizes) const noexcept;
	
	/**
	 * Sets the tensor's values using raw bytes
	 * 
	 * @param Values Array of values as bytes
	 * @param Sizes Array of sizes
	 */
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor")
	virtual void SetSerializedValues(const TArray<uint8>& Values, const TArray<int64>& Sizes) noexcept;
	
	/**
	 * Creates a new tensor and copies the data over from the original
	 * 
	 * @param OutClone Cloned tensor
	 * @param Outer Clone's outer object
	 */
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor")
	virtual void CloneData(TScriptInterface<IAtumTensor>& OutClone, UObject* Outer = nullptr) const noexcept;
	
	/**
	 * Computes this tensor's gradient
	 * 
	 * @param Gradient Tensor that's multiplied with the derivative
	 * @param Inputs Tensors which the gradient will be accumulated into
	 * @param RetainGraphMode How to retain the graph
	 * @param bCreateGraph Should the graph of the derivative be created?
	 * @return Was the gradient computed?
	 */
	UFUNCTION(BlueprintPure = "false", Category = "ATUM|Tensor", meta = (
		AdvancedDisplay = "Gradient,Inputs,RetainGraphMode,bCreateGraph",
		AutoCreateRefTerm = "Gradient,Inputs"
	))
	virtual bool Backward(
		const TScriptInterface<IAtumTensor>& Gradient,
		const TArray<TScriptInterface<IAtumTensor>>& Inputs,
		EAtumTensorRetainGraphMode RetainGraphMode = EAtumTensorRetainGraphMode::IfCreated,
		bool bCreateGraph = false
	) const noexcept;
	
	/**
	 * Gets the LibTorch device on which this tensor sits
	 * 
	 * @return This tensor's LibTorch device type
	 */
	[[nodiscard]]
	FORCEINLINE c10::DeviceType GetTorchDeviceType() const noexcept { return AtumEnums::Cast(GetDeviceType()); }
	
	/**
	 * Gets the LibTorch type of value this tensor holds
	 * 
	 * @return This tensor's LibTorch scalar type
	 */
	[[nodiscard]]
	FORCEINLINE c10::ScalarType GetTorchScalarType() const noexcept
	{ return Data ? Data->scalar_type() : AtumEnums::Cast(GetScalarType()); }
	
	/**
	 * Adds two tensors together
	 * 
	 * @param Other Tensor to add with the original
	 * @param Class Class of resulting tensor
	 * @return Sum of the tensors
	 */
	[[nodiscard]]
	TScriptInterface<IAtumTensor> Add(
		const TScriptInterface<IAtumTensor>& Other,
		UPARAM(meta = (MustImplement = "/Script/Atum.AtumTensor")) const UClass* Class = nullptr
	) const noexcept;
	
	/**
	 * Adds two tensors together by overloading the + operator
	 * 
	 * @param Other Tensor to add with the original
	 * @return Sum of the tensors
	 */
	[[nodiscard]]
	FORCEINLINE TScriptInterface<IAtumTensor> operator+(const TScriptInterface<IAtumTensor>& Other) const noexcept
	{ return Add(Other); }
	
	/**
	 * Returns the tensor as a string by overloading the FString cast operator
	 */
	[[nodiscard]]
	explicit operator FString() const noexcept;
	
	/**
	 * Casts a tensor to a string
	 * 
	 * @return This tensor as a string
	 */
	[[nodiscard]]
	FORCEINLINE FString ToString() const noexcept { return static_cast<FString>(*this); }
	
	/**
	 * Gets the tensor one dimension lower at a specific index by overloading the [] operator
	 * 
	 * @param Index Long integer
	 * @return Inner tensor
	 */
	[[nodiscard]]
	FORCEINLINE at::Tensor operator[](const int64 Index) { return (*Data)[Index]; }
	
	/**
	 * Gets the tensor one dimension lower at a specific index by overloading the [] operator
	 * 
	 * @param Scalar Any type of scalar
	 * @return Inner tensor
	 */
	[[nodiscard]]
	FORCEINLINE at::Tensor operator[](const c10::Scalar& Scalar) { return (*Data)[Scalar]; }
	
	/**
	 * Gets the tensor one dimension lower at a specific index by overloading the [] operator
	 * 
	 * @param Tensor 0D tensor
	 * @return Inner tensor
	 */
	[[nodiscard]]
	FORCEINLINE at::Tensor operator[](const at::Tensor& Tensor) { return (*Data)[Tensor]; }
	
	/**
	 * Gets the tensor one dimension lower at a specific index by overloading the [] operator
	 * 
	 * @param Tensor 0D tensor
	 * @return Inner tensor
	 */
	[[nodiscard]]
	FORCEINLINE at::Tensor operator[](const IAtumTensor& Tensor) { return (*Data)[*Tensor.Data]; }
	
	/**
	 * Gets the values and sizes of this tensor regardless of the scalar type
	 * 
	 * @tparam T Type of element
	 * @param OutValues Array of values
	 * @param OutSizes Array of sizes
	 */
	template <typename T>
	void GetValues(TArray<T>& OutValues, TArray<int64>& OutSizes) const noexcept;
	
	/**
	 * Sets the values and sizes of this tensor regardless of the scalar type
	 * 
	 * @tparam T Type of element
	 * @param Values Array beginning of new values
	 * @param Sizes Array of new sizes
	 */
	template <typename T>
	FORCEINLINE void SetValues(T* const Values, const TArray<int64>& Sizes) noexcept
	{
		try
		{
			SetData(torch::from_blob(
				Values,
				c10::IntArrayRef(Sizes.GetData(), Sizes.Num()),
				GetTorchScalarType()
			).to(GetTorchDeviceType()));
		}
		catch (const std::exception& Exception)
		{
			UE_LOG(LogTemp, Fatal, TEXT("%hs"), Exception.what())
		}
	}
	
protected:
	/**
	 * Blueprint function to call IAtumTensor::SetRequireGradient
	 * 
	 * @param bValue Is the gradient required?
	 * @param OutSelf The tensor itself
	 */
	UFUNCTION(BlueprintCallable, Category = "ATUM|Tensor", DisplayName = "Set Require Gradient")
	virtual void K2_SetRequireGradient(bool bValue, TScriptInterface<IAtumTensor>& OutSelf) noexcept;
	
	/**
	 * Saves the tensor data to a file
	 * 
	 * @param RelativePath Path to file relative to ATUM's Content folder
	 * @return Was the operation successful?
	 */
	virtual bool SaveToFile_Implementation(const FString& RelativePath) const override;
	
	/**
	 * Loads the tensor data from a file
	 * 
	 * @param RelativePath Path to file relative to ATUM's Content folder
	 * @return Was the operation successful?
	 */
	virtual bool LoadFromFile_Implementation(const FString& RelativePath) override;
	
private:
	/**
	 * Gets the values as any scalar type
	 * 
	 * @param Type LibTorch scalar type
	 * @return Generic pointer to the data
	 */
	[[nodiscard]]
	FORCEINLINE void* GetUncastedValues(const c10::ScalarType Type) const noexcept
	{ return IsDefined() ? Data->to(Type).data_ptr() : nullptr; }
	
	/**
	 * Gets the values as any scalar type
	 * 
	 * @param Type ATUM scalar type
	 * @return Generic pointer to the data
	 */
	[[nodiscard]]
	FORCEINLINE void* GetUncastedValues(const EAtumTensorScalarType Type) const noexcept
	{ return GetUncastedValues(AtumEnums::Cast(Type)); }

	/**
	 * Writes this tensor as a string inside a stream by overloading the << operator
	 * 
	 * @param OutStream Output stream
	 * @param AtumTensor The tensor
	 * @return The modified stream
	 */
	friend std::ostream& operator<<(std::ostream& OutStream, const IAtumTensor& AtumTensor) noexcept;
	
	/**
	 * Writes this tensor as a string inside a stream by overloading the << operator
	 * 
	 * @param OutStream Output stream
	 * @param AtumTensor The tensor
	 * @return The modified stream
	 */
	friend std::ostream& operator<<(std::ostream& OutStream, const TScriptInterface<IAtumTensor>& AtumTensor) noexcept;
	
public:
	/**
	 * Getter for DefaultDeviceType
	 */
	[[nodiscard]]
	static FORCEINLINE EAtumTensorDeviceType GetDefaultDeviceType() noexcept { return DefaultDeviceType; }
	
	/**
	 * Setter for DefaultDeviceType
	 */
	static FORCEINLINE void SetDefaultDeviceType(const EAtumTensorDeviceType Value) noexcept
	{ DefaultDeviceType = Value; }
	
	/**
	 * Getter for Data as a pointer
	 */
	[[nodiscard]]
	FORCEINLINE const at::Tensor* GetData() const noexcept { return Data.Get(); }
	
	/**
	 * Getter for Data as a reference
	 */
	[[nodiscard]]
	FORCEINLINE const at::Tensor& GetDataChecked() const { return *GetData(); }
	
	/**
	 * Setter for Data
	 */
	FORCEINLINE void SetData(const at::Tensor& Value) noexcept
	{
		Data.Reset(Value.defined() ?
			new at::Tensor(Value.to(GetTorchDeviceType()).to(GetTorchScalarType())) :
			nullptr
		);
	}
};


/**
 * Templated part of the tensor interface
 * @tparam T Scalar value type
 */
template <typename T>
class TAtumTensor
{
protected:
	/**
	 * Container for values after being set with templates to maintain the reference
	 */
	mutable TArray<T> InternalValues = TArray<T>();
	
	/**
	 * Sets the internal values and keeps the input array
	 * 
	 * @param AtumTensor Tensor interface reference
	 * @param Values Array of values to set
	 * @param Sizes Array of sizes
	 */
	void SetInternalValues(IAtumTensor& AtumTensor, const TArray<T>& Values, const TArray<int64>& Sizes) noexcept;

public:
	/**
	 * Getter for InternalValues
	 */
	[[nodiscard]]
	FORCEINLINE const TArray<T>& GetInternalValues() const noexcept { return InternalValues; }
	
	/**
	 * Getter for InternalValues
	 */
	FORCEINLINE void GetInternalValues(TArray<T>& OutValues) noexcept { OutValues = InternalValues; }
};


template <typename T>
void IAtumTensor::GetValues(TArray<T>& OutValues, TArray<int64>& OutSizes) const noexcept
{
	if (!IsDefined())
		return;
	
	OutValues.Append(static_cast<T*>(GetUncastedValues(GetScalarType())), Data->numel());
	
	const c10::IntArrayRef DataSizes = Data->sizes();
	OutSizes = TArray(DataSizes.data(), DataSizes.size());
}

template <typename T>
void TAtumTensor<T>::SetInternalValues(
	IAtumTensor& AtumTensor,
	const TArray<T>& Values,
	const TArray<int64>& Sizes
) noexcept
{
	InternalValues = Values;
	AtumTensor.SetValues<T>(InternalValues.GetData(), Sizes);
}

#undef LOCTEXT_NAMESPACE
