#include <exception>
#include <cstddef>

#include "factorization_c_api.h"
#include "matrix.hpp"
#include "factorization.hpp"

void _cholesky_decomposition(cmatrix in, cmatrix out, size_t n) {
  try {
    auto matrix = (float *)in;
    auto cpp_matrix = Matrix<float>(n, Row<float>(n));
    for(size_t i = 0; i < n; ++i) {
      for(size_t j = 0; j < n; ++j) {
        cpp_matrix[i][j] = matrix[i*n + j];
      }
    }
    auto res = cholesky_decomposition(cpp_matrix);
    for(size_t i = 0; i < n; ++i) {
      for(size_t j = 0; j < n; ++j) {
        if(j <= i) {
          ((float *)out)[i*n + j] = res[i][j];
        } else {
          ((float *)out)[i*n + j] = 0;
        }
      }
    }
  } catch (std::exception const& e) {
    return;
  }
}
