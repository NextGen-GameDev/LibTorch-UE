// © 2023 Kaya Adrian.

#pragma once

#include "Macros/AtumMacrosGuards.h"


#include <c10/core/DeviceType.h>


#include "AtumTensorDeviceType.generated.h"


#define LOCTEXT_NAMESPACE "AtumTensorDeviceType"

/**
 * Represents every type of device that a tensor can be used in
 */
UENUM(BlueprintType, Category = "ATUM|Tensor", DisplayName = "ATUM Tensor Device Type", meta = (
	Keywords = "ATUM Tensor Device Type"
))
enum class EAtumTensorDeviceType : uint8
{
	// CPU
	Cpu = c10::DeviceType::CPU UMETA(DisplayName = "CPU"),
	// CUDA
	Cuda = c10::DeviceType::CUDA UMETA(DisplayName = "CUDA"),
	// Explicit MKLDNN
	MklDnn = c10::DeviceType::MKLDNN UMETA(DisplayName = "MKLDNN"),
	// OpenGL
	OpenGL = c10::DeviceType::OPENGL UMETA(DisplayName = "OpenGL"),
	// OpenCL
	OpenCL = c10::DeviceType::OPENCL UMETA(DisplayName = "OpenCL"),
	// iDeep
	IDeep = c10::DeviceType::IDEEP UMETA(DisplayName = "iDeep"),
	// AMD HIP
	Hip = c10::DeviceType::HIP UMETA(DisplayName = "HIP"),
	// FPGA
	Fpga = c10::DeviceType::FPGA UMETA(DisplayName = "FPGA"),
	// ONNX Runtime
	Ort = c10::DeviceType::ORT UMETA(DisplayName = "ONNX Runtime"),
	// XLA / TPU
	Xla = c10::DeviceType::XLA UMETA(DisplayName = "XLA"),
	// Vulkan
	Vulkan = c10::DeviceType::Vulkan UMETA(DisplayName = "Vulkan"),
	// Metal
	Metal = c10::DeviceType::Metal UMETA(DisplayName = "Metal"),
	// XPU
	Xpu = c10::DeviceType::XPU UMETA(DisplayName = "XPU"),
	// MPS
	Mps = c10::DeviceType::MPS UMETA(DisplayName = "MPS"),
	// Meta (tensors with no data)
	Meta = c10::DeviceType::Meta UMETA(DisplayName = "Meta"),
	// HPU / HABANA
	Hpu = c10::DeviceType::HPU UMETA(DisplayName = "HPU"),
	// SX-Aurora / NEC
	Ve = c10::DeviceType::VE UMETA(DisplayName = "VE"),
	// Lazy tensors
	Lazy = c10::DeviceType::Lazy UMETA(DisplayName = "Lazy"),
	// Graphcore IPU
	Ipu = c10::DeviceType::IPU UMETA(DisplayName = "IPU"),
	// Meta training and inference
	Mtia = c10::DeviceType::MTIA UMETA(DisplayName = "MTIA"),
	// PrivateUse1
	PrivateUse1 = c10::DeviceType::PrivateUse1 UMETA(DisplayName = "PrivateUse1"),
	// Number of types
	TypesCount = c10::DeviceType::COMPILE_TIME_MAX_DEVICE_TYPES UMETA(Hidden, DisplayName = "Types Count")
};


namespace AtumEnums
{
	/**
	 * Transforms an ATUM enum value into a LibTorch enum value
	 * 
	 * @param DeviceType ATUM-equivalent device
	 * @return LibTorch-equivalent device
	 */
	[[nodiscard]]
	static FORCEINLINE CONSTEXPR c10::DeviceType Cast(const EAtumTensorDeviceType DeviceType) noexcept
	{ return static_cast<c10::DeviceType>(DeviceType); }

	/**
	 * Transforms a LibTorch enum value into an ATUM enum value
	 * 
	 * @param DeviceType LibTorch-equivalent device
	 * @return ATUM-equivalent device
	 */
	[[nodiscard]]
	static FORCEINLINE CONSTEXPR EAtumTensorDeviceType Cast(const c10::DeviceType DeviceType) noexcept
	{ return static_cast<EAtumTensorDeviceType>(DeviceType); }
}

#undef LOCTEXT_NAMESPACE
