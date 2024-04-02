// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Models/Llama/LlamaUnreal.h"
#include "Models/Llama/llama_utils.h"

#include "IAtumModule.h"
#include "Macros/AtumMacrosLog.h"
#include "Misc/Paths.h"

#include "Tensors/IAtumTensor.h"





bool ULlamaUnreal::OnInitializeData_Implementation(const bool bRetry)
{
	UE_LOG(LogTemp, Warning, TEXT("ULlamaUnreal::OnInitializeData_Implementation"));
	auto LlamaOptions = static_cast<LlamaConfig>(Options);
	// LlamaOptions.dtype = torch::kFloat32;
	Module = MakeShared<LlamaCausalLM>(std::make_shared<LlamaCausalLMImpl>(
		LlamaOptions
	));
	return true;
}


bool ULlamaUnreal::LoadFromFile_Implementation(const FString& RelativePath)
{
	
	if (!IAtumLayer::LoadFromFile_Implementation(RelativePath))
		return false;


	Options.SetFrom((*Module)->config);
	
	return true;
}



bool ULlamaUnreal::OnForward_Implementation(
	const TScriptInterface<IAtumTensor>& Input,
	TScriptInterface<IAtumTensor>& Output
)
{
	TArray<int64> InputSizes;
	Input->GetSizes(InputSizes);

	if (InputSizes.IsEmpty())
	{
		ATUM_LOG(Error, TEXT("Cannot use 0D input tensor!"))
		return false;
	}


	
	auto const LmOutputs = (*Module)(Input->GetDataChecked().to(c10::kLong));  // Embedding typically requires Long type indices

	

	Output = DuplicateObject(Input.GetObject(), nullptr);

	// set Output type as float32
	Output->SetScalarType(EAtumTensorScalarType::Float);

	// set output data
	Output->SetData(std::get<0>(LmOutputs));
	
	
	return true;
}

void ULlamaUnreal::SetOptions(const FAtumLlamaOptions& NewOptions)
{
	Options = NewOptions;
}

bool ULlamaUnreal::Generate_Implementation(const TScriptInterface<IAtumTensor>& Input, TScriptInterface<IAtumTensor>& Output, const int32& NumNewTokens  = 10)
{

	TArray<int64> InputSizes;
	Input->GetSizes(InputSizes);

	if (InputSizes.IsEmpty())
	{
		ATUM_LOG(Error, TEXT("Cannot use 0D input tensor!"))
		return false;
	}

	
	
	auto implPtr = std::dynamic_pointer_cast<LlamaCausalLMImpl>(Module->ptr());

	implPtr->eval();


	torch::Tensor InputTensor = Input->GetDataChecked().to(c10::kLong);
	
	auto const LmOutputs = implPtr->generate(InputTensor, NumNewTokens);
	Output = DuplicateObject(Input.GetObject(), nullptr);

	Output->SetData(LmOutputs);

	return true;
	

}

bool ULlamaUnreal::LoadParams_Implementation(const FString& Path)
{

	FString const FilePath = IAtumModule::GetContentDirectory(Path);
	if (!FPaths::FileExists(FilePath))
	{
		// Handle the case where the file doesn't exist if needed
		UE_LOG(LogTemp, Warning, TEXT("File does not exist: %s"), *FilePath);
		return false;  
	}

	UE_LOG(LogTemp, Warning, TEXT("File exists: %s"), *FilePath);
	std::string StdPath = TCHAR_TO_UTF8(*FilePath);
	
	
	torch::load(*Module, StdPath);


	UE_LOG(LogTemp, Warning, TEXT("Loaded parameters"));
	return true;
}


bool ULlamaUnreal::ToArchive_Implementation(const FString& InPath, const FString& OutPath)
{


	FString const FilePath = IAtumModule::GetContentDirectory(InPath);
	if (!FPaths::FileExists(FilePath))
	{
		// Handle the case where the file doesn't exist if needed
		UE_LOG(LogTemp, Warning, TEXT("File does not exist: %s"), *FilePath);
		return false;  
	}

	UE_LOG(LogTemp, Warning, TEXT("File exists: %s"), *FilePath);
	std::string StdPath = TCHAR_TO_UTF8(*FilePath);
	


	FString const OutFilePath = IAtumModule::GetContentDirectory(OutPath);
	
	ArchiveConverter converter;
	converter.toOutputArchive(StdPath, TCHAR_TO_UTF8(*OutFilePath));

	return true;
}

