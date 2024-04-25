#pragma once

namespace torch {
namespace autograd {
namespace generated {

PyTypeObject* get__fake_quantize_per_tensor_affine_cachemask_tensor_qparams_namedtuple();
PyTypeObject* get__fused_moving_avg_obs_fq_helper_namedtuple();
PyTypeObject* get__linalg_det_namedtuple();
PyTypeObject* get__linalg_det_out_namedtuple();
PyTypeObject* get__linalg_eigh_namedtuple();
PyTypeObject* get__linalg_eigh_out_namedtuple();
PyTypeObject* get__linalg_slogdet_namedtuple();
PyTypeObject* get__linalg_slogdet_out_namedtuple();
PyTypeObject* get__linalg_solve_ex_namedtuple();
PyTypeObject* get__linalg_solve_ex_out_namedtuple();
PyTypeObject* get__linalg_svd_namedtuple();
PyTypeObject* get__linalg_svd_out_namedtuple();
PyTypeObject* get__lu_with_info_namedtuple();
PyTypeObject* get__scaled_dot_product_efficient_attention_namedtuple();
PyTypeObject* get__scaled_dot_product_flash_attention_namedtuple();
PyTypeObject* get__unpack_dual_namedtuple();
PyTypeObject* get_aminmax_namedtuple();
PyTypeObject* get_aminmax_out_namedtuple();
PyTypeObject* get_cummax_namedtuple();
PyTypeObject* get_cummax_out_namedtuple();
PyTypeObject* get_cummin_namedtuple();
PyTypeObject* get_cummin_out_namedtuple();
PyTypeObject* get_frexp_namedtuple();
PyTypeObject* get_frexp_out_namedtuple();
PyTypeObject* get_geqrf_out_namedtuple();
PyTypeObject* get_geqrf_namedtuple();
PyTypeObject* get_histogram_out_namedtuple();
PyTypeObject* get_histogram_namedtuple();
PyTypeObject* get_histogramdd_namedtuple();
PyTypeObject* get_kthvalue_namedtuple();
PyTypeObject* get_kthvalue_out_namedtuple();
PyTypeObject* get_linalg_cholesky_ex_namedtuple();
PyTypeObject* get_linalg_cholesky_ex_out_namedtuple();
PyTypeObject* get_linalg_eig_namedtuple();
PyTypeObject* get_linalg_eig_out_namedtuple();
PyTypeObject* get_linalg_eigh_namedtuple();
PyTypeObject* get_linalg_eigh_out_namedtuple();
PyTypeObject* get_linalg_inv_ex_namedtuple();
PyTypeObject* get_linalg_inv_ex_out_namedtuple();
PyTypeObject* get_linalg_ldl_factor_namedtuple();
PyTypeObject* get_linalg_ldl_factor_out_namedtuple();
PyTypeObject* get_linalg_ldl_factor_ex_namedtuple();
PyTypeObject* get_linalg_ldl_factor_ex_out_namedtuple();
PyTypeObject* get_linalg_lstsq_namedtuple();
PyTypeObject* get_linalg_lstsq_out_namedtuple();
PyTypeObject* get_linalg_lu_namedtuple();
PyTypeObject* get_linalg_lu_out_namedtuple();
PyTypeObject* get_linalg_lu_factor_namedtuple();
PyTypeObject* get_linalg_lu_factor_out_namedtuple();
PyTypeObject* get_linalg_lu_factor_ex_namedtuple();
PyTypeObject* get_linalg_lu_factor_ex_out_namedtuple();
PyTypeObject* get_linalg_qr_namedtuple();
PyTypeObject* get_linalg_qr_out_namedtuple();
PyTypeObject* get_linalg_slogdet_namedtuple();
PyTypeObject* get_linalg_slogdet_out_namedtuple();
PyTypeObject* get_linalg_solve_ex_namedtuple();
PyTypeObject* get_linalg_solve_ex_out_namedtuple();
PyTypeObject* get_linalg_svd_namedtuple();
PyTypeObject* get_linalg_svd_out_namedtuple();
PyTypeObject* get_lu_unpack_namedtuple();
PyTypeObject* get_lu_unpack_out_namedtuple();
PyTypeObject* get_max_namedtuple();
PyTypeObject* get_max_out_namedtuple();
PyTypeObject* get_median_namedtuple();
PyTypeObject* get_median_out_namedtuple();
PyTypeObject* get_min_namedtuple();
PyTypeObject* get_min_out_namedtuple();
PyTypeObject* get_mode_namedtuple();
PyTypeObject* get_mode_out_namedtuple();
PyTypeObject* get_nanmedian_namedtuple();
PyTypeObject* get_nanmedian_out_namedtuple();
PyTypeObject* get_qr_out_namedtuple();
PyTypeObject* get_qr_namedtuple();
PyTypeObject* get_slogdet_namedtuple();
PyTypeObject* get_slogdet_out_namedtuple();
PyTypeObject* get_sort_out_namedtuple();
PyTypeObject* get_sort_namedtuple();
PyTypeObject* get_svd_out_namedtuple();
PyTypeObject* get_svd_namedtuple();
PyTypeObject* get_topk_out_namedtuple();
PyTypeObject* get_topk_namedtuple();
PyTypeObject* get_triangular_solve_out_namedtuple();
PyTypeObject* get_triangular_solve_namedtuple();

}

void initReturnTypes(PyObject* module);

} // namespace autograd
} // namespace torch
