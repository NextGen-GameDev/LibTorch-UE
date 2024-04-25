#pragma once

// @generated by torchgen/gen.py from Function.h

#include <ATen/Context.h>
#include <ATen/DeviceGuard.h>
#include <ATen/TensorUtils.h>
#include <ATen/TracerMode.h>
#include <ATen/core/Generator.h>
#include <ATen/core/Reduction.h>
#include <ATen/core/Tensor.h>
#include <c10/core/Scalar.h>
#include <c10/core/Storage.h>
#include <c10/core/TensorOptions.h>
#include <c10/util/Deprecated.h>
#include <c10/util/Optional.h>



#include <ATen/ops/miopen_convolution_relu_ops.h>

namespace at {


// aten::miopen_convolution_relu(Tensor self, Tensor weight, Tensor? bias, SymInt[] stride, SymInt[] padding, SymInt[] dilation, SymInt groups) -> Tensor
inline at::Tensor miopen_convolution_relu(const at::Tensor & self, const at::Tensor & weight, const c10::optional<at::Tensor> & bias, at::IntArrayRef stride, at::IntArrayRef padding, at::IntArrayRef dilation, int64_t groups) {
    return at::_ops::miopen_convolution_relu::call(self, weight, bias, c10::fromIntArrayRefSlow(stride), c10::fromIntArrayRefSlow(padding), c10::fromIntArrayRefSlow(dilation), groups);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same<T, int64_t>::value>>
  at::Tensor miopen_convolution_relu(const at::Tensor & self, const at::Tensor & weight, const c10::optional<at::Tensor> & bias, at::IntArrayRef stride, at::IntArrayRef padding, at::IntArrayRef dilation, int64_t groups) {
    return at::_ops::miopen_convolution_relu::call(self, weight, bias, c10::fromIntArrayRefSlow(stride), c10::fromIntArrayRefSlow(padding), c10::fromIntArrayRefSlow(dilation), groups);
  }
}

// aten::miopen_convolution_relu(Tensor self, Tensor weight, Tensor? bias, SymInt[] stride, SymInt[] padding, SymInt[] dilation, SymInt groups) -> Tensor
inline at::Tensor miopen_convolution_relu_symint(const at::Tensor & self, const at::Tensor & weight, const c10::optional<at::Tensor> & bias, c10::SymIntArrayRef stride, c10::SymIntArrayRef padding, c10::SymIntArrayRef dilation, c10::SymInt groups) {
    return at::_ops::miopen_convolution_relu::call(self, weight, bias, stride, padding, dilation, groups);
}
namespace symint {
  template <typename T, typename = std::enable_if_t<std::is_same<T, c10::SymInt>::value>>
  at::Tensor miopen_convolution_relu(const at::Tensor & self, const at::Tensor & weight, const c10::optional<at::Tensor> & bias, c10::SymIntArrayRef stride, c10::SymIntArrayRef padding, c10::SymIntArrayRef dilation, c10::SymInt groups) {
    return at::_ops::miopen_convolution_relu::call(self, weight, bias, stride, padding, dilation, groups);
  }
}

}
