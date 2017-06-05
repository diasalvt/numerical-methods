#ifndef FACTORIZATION_HPP
#define FACTORIZATION_HPP

#include "matrix.hpp"
#include <cmath>
#include <cstddef>
#include <iostream>

template <class T>
Matrix<T> cholesky_decomposition(const Matrix<T>& A) {
  auto L = Matrix<T>(A.size(), Row<T>(A.size()));

  for(size_t i = 0; i < A.size(); ++i) {
    for(size_t j = 0; j <= i; ++j) {
      T sum = 0;
      for(size_t k = 0; k < j; ++k) {
        sum += L[i][k] * L[j][k];
      }

      if(i == j) {
        L[i][i] = std::sqrt(A[i][i] - sum);
      } else {
        L[i][j] = (A[i][j] - sum) / L[j][j];
      }
    }
  }

  return L;
}

#endif
