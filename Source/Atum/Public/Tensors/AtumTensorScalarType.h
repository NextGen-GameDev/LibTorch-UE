// © 2023 Kaya Adrian.

#pragma once

#include "Macros/AtumMacrosGuards.h"

#include "GenericPlatform/GenericPlatformCompilerPreSetup.h"
TORCH_INCLUDES_START
#include <c10/core/ScalarType.h>
TORCH_INCLUDES_END


#include "AtumTensorScalarType.generated.h"


#define LOCTEXT_NAMESPACE "AtumTensorScalarType"

/**
 * Represents every type of scalar that can be used within tensors
 */
UENUM(BlueprintType, Category = "ATUM|Tensor", DisplayName = "ATUM Tensor Scalar Type", meta = (
	Keywords = "ATUM Tensor Scalar Type"
))
enum class EAtumTensorScalarType : uint8
{
	Byte = c10::ScalarType::Byte UMETA(DisplayName = "Byte"), // uint8
	Char = c10::ScalarType::Char UMETA(DisplayName = "Char"), // int8
	Short = c10::ScalarType::Short UMETA(DisplayName = "Short"), // int16
	Int = c10::ScalarType::Int UMETA(DisplayName = "Int"), // int
	Long = c10::ScalarType::Long UMETA(DisplayName = "Long"), // int64
	Half = c10::ScalarType::Half UMETA(DisplayName = "Half"), // at::Half
	Float = c10::ScalarType::Float UMETA(DisplayName = "Float"), // float
	Double = c10::ScalarType::Double UMETA(DisplayName = "Double"), // double
	CHalf = c10::ScalarType::ComplexHalf UMETA(DisplayName = "Complex Half"), // c10::complex<c10::Half>
	CFloat = c10::ScalarType::ComplexFloat UMETA(DisplayName = "Complex Float"), // c10::complex<float>
	CDouble = c10::ScalarType::ComplexDouble UMETA(DisplayName = "Complex Double"), // c10::complex<double>
	Boolean = c10::ScalarType::Bool UMETA(DisplayName = "Boolean"), // bool
	QChar = c10::ScalarType::QInt8 UMETA(DisplayName = "QChar"), // c10::qint8
	QByte = c10::ScalarType::QUInt8 UMETA(DisplayName = "QByte"), // c10::quint8
	QInt = c10::ScalarType::QInt32 UMETA(DisplayName = "QInt"), // c10::qint32
	BHalf = c10::ScalarType::BFloat16 UMETA(DisplayName = "BHalf"), // at::BFloat16
	Q4X2 = c10::ScalarType::QUInt4x2 UMETA(DisplayName = "QUInt4X2"), // c10::quint4x2
	Q2X4 = c10::ScalarType::QUInt2x4 UMETA(DisplayName = "QUInt2X4"), // c10::quint2x4
	Undefined = c10::ScalarType::Undefined UMETA(DisplayName = "Undefined"), // Invalid type
	TypesCount = c10::ScalarType::NumOptions UMETA(Hidden, DisplayName = "Types Count") // Number of types
};


namespace AtumEnums
{
	/**
	 * Transforms an ATUM enum value into a LibTorch enum value
	 * 
	 * @param ScalarType ATUM-equivalent scalar
	 * @return LibTorch-equivalent scalar
	 */
	[[nodiscard]]
	static FORCEINLINE CONSTEXPR c10::ScalarType Cast(const EAtumTensorScalarType ScalarType) noexcept
	{ return static_cast<c10::ScalarType>(ScalarType); }
	
	/**
	 * Transforms a LibTorch enum value into an ATUM enum value
	 * 
	 * @param ScalarType LibTorch-equivalent scalar
	 * @return ATUM-equivalent scalar
	 */
	[[nodiscard]]
	static FORCEINLINE CONSTEXPR EAtumTensorScalarType Cast(const c10::ScalarType ScalarType) noexcept
	{ return static_cast<EAtumTensorScalarType>(ScalarType); }
}

#undef LOCTEXT_NAMESPACE
