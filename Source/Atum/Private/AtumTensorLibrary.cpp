﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "AtumTensorLibrary.h"

#include "IAtum.h"
#include "Kismet/KismetArrayLibrary.h"

#include <ranges>


void UAtumTensorLibrary::K2_SerializeArray(
	[[maybe_unused]] const TArray<UProperty*>& Target,
	[[maybe_unused]] TArray<uint8>& OutBytes
) noexcept
{
	UE_LOG(LogAtum, Warning, TEXT("Called UAtumUtilities::K2_SerializeArray from native code!"))
}

void UAtumTensorLibrary::K2_DeserializeArray(
	[[maybe_unused]] const TArray<uint8>& Bytes,
	[[maybe_unused]] TArray<UProperty*>& InTarget,
	[[maybe_unused]] TArray<UProperty*>& OutTarget
) noexcept
{
	UE_LOG(LogAtum, Warning, TEXT("Called UAtumUtilities::K2_DeserializeArray from native code!"))
}

UObject* UAtumTensorLibrary::Eye(const TSubclassOf<UObject> Class, const int64 Size) noexcept
{
	check(Class->ImplementsInterface(UAtumTensor::StaticClass()))
	
	auto* const Tensor = NewObject<UObject>(GetTransientPackage(), Class);
	CastChecked<IAtumTensor>(Tensor)->SetData(torch::eye(Size));
	return Tensor;
}

void UAtumTensorLibrary::GenericArray_Serialize(
	const uint8* const TargetAddress,
	const FArrayProperty* const TargetProperty,
	TArray<uint8>& OutBytes
) noexcept
{
	check(TargetProperty)
	if (TargetAddress)
	{
		FScriptArrayHelper TargetArray(TargetProperty, TargetAddress);
		OutBytes = TArray(TargetArray.GetRawPtr(), TargetArray.Num() * TargetProperty->Inner->GetSize());
	}
}

void UAtumTensorLibrary::GenericArray_Deserialize(
	const TArray<uint8>& Bytes,
	uint8* const OutTargetAddress,
	const FArrayProperty* const OutTargetProperty
) noexcept
{
	check(OutTargetProperty)
	if (OutTargetAddress == nullptr)
		return;
	
	const FProperty* const OutTargetInnerProperty = OutTargetProperty->Inner;
	const int32 ElementSize = OutTargetInnerProperty->GetSize();
	const int32 ElementCount = Bytes.Num() / ElementSize;

	FScriptArrayHelper OutTargetArray(OutTargetProperty, OutTargetAddress);
	OutTargetArray.AddValues(ElementCount);

	const uint8* Source = Bytes.GetData();
	uint8* Destination = OutTargetArray.GetRawPtr();
	
	for ([[maybe_unused]] const int32 Dummy : std::ranges::iota_view(0, ElementCount))
	{
		OutTargetInnerProperty->CopySingleValueToScriptVM(Destination, Source);
		Source += ElementSize;
		Destination += ElementSize;
	}
}

// ReSharper disable CppUE4CodingStandardNamingViolationWarning
void UAtumTensorLibrary::execK2_SerializeArray(
	[[maybe_unused]] UObject* const Context,
	FFrame& Stack,
	[[maybe_unused]] void* const Z_Param__Result
) noexcept
{
	Stack.MostRecentProperty = nullptr;
	Stack.StepCompiledIn<FArrayProperty>(nullptr);

	const uint8* const TargetAddress = Stack.MostRecentPropertyAddress;
	const FArrayProperty* const TargetProperty = CastField<FArrayProperty>(Stack.MostRecentProperty);
	if (TargetProperty == nullptr)
	{
		Stack.bArrayContextFailed = true;
		return;
	}

	P_GET_TARRAY_REF(uint8, OutBytes)
	
	P_FINISH
		
	P_NATIVE_BEGIN
	GenericArray_Serialize(TargetAddress, TargetProperty, OutBytes);
	P_NATIVE_END
}

void UAtumTensorLibrary::execK2_DeserializeArray(
	[[maybe_unused]] UObject* const Context,
	FFrame& Stack,
	[[maybe_unused]] void* const Z_Param__Result
) noexcept
{
	TArray<uint8> BytesTemp;
	const TArray<uint8>& Bytes = Stack.StepCompiledInRef<FArrayProperty, TArray<uint8>>(&BytesTemp);

	Stack.MostRecentProperty = nullptr;
	Stack.StepCompiledIn<FArrayProperty>(nullptr);

	uint8* const InTargetAddress = Stack.MostRecentPropertyAddress;
	const FArrayProperty* const InTargetProperty = CastField<FArrayProperty>(Stack.MostRecentProperty);
	if (InTargetProperty == nullptr)
	{
		Stack.bArrayContextFailed = true;
		return;
	}
	if (CastField<FArrayProperty>(Stack.MostRecentProperty) == nullptr)
	{
		Stack.bArrayContextFailed = true;
		return;
	}

	Stack.MostRecentProperty = nullptr;
	Stack.StepCompiledIn<FArrayProperty>(nullptr);

	uint8* const OutTargetAddress = Stack.MostRecentPropertyAddress;
	const FArrayProperty* const OutTargetProperty = CastField<FArrayProperty>(Stack.MostRecentProperty);
	if (OutTargetProperty == nullptr)
	{
		Stack.bArrayContextFailed = true;
		return;
	}
	
	P_FINISH
	
	P_NATIVE_BEGIN
	GenericArray_Deserialize(Bytes, InTargetAddress, InTargetProperty);
	UKismetArrayLibrary::GenericArray_Append(
		OutTargetAddress,
		OutTargetProperty,
		InTargetAddress,
		InTargetProperty
	);
	P_NATIVE_END
}

void UAtumTensorLibrary::execConv_TensorToString(
	[[maybe_unused]] UObject* const Context,
	FFrame& Stack,
	void* const Z_Param__Result
)
{
	TScriptInterface<const IAtumTensor> TensorTemp;
	const TScriptInterface<const IAtumTensor>& Tensor = Stack
	.StepCompiledInRef<FInterfaceProperty, TScriptInterface<const IAtumTensor>>(&TensorTemp);
		
	P_FINISH
		
	P_NATIVE_BEGIN
	*static_cast<FString*>(Z_Param__Result) = Conv_TensorToString(Tensor);
	P_NATIVE_END
}
// ReSharper restore CppUE4CodingStandardNamingViolationWarning
