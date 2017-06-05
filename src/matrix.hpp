#ifndef MATRIX_HPP
#define MATRIX_HPP

#include<vector>
#include <iostream>
#include <stdint.h>
#include "Eigen/Core"

/* Templated Typedef C++11 */
template <class T>
using Matrix = std::vector<std::vector<T > >;

template <class T>
using Row = std::vector<T >;

template <class T>
void load_cmatrix(T* in, Matrix<T>& mat, size_t n, size_t m) {
  for(size_t i = 0; i < n; ++i) {
    for(size_t j = 0; j < m; ++j) {
      mat[i][j] = in[i*m + j];
    }
  }
}

template <class T>
void output_to_cmatrix(T* out, Matrix<T>& mat, size_t n, size_t m) {
  for(size_t i = 0; i < n; ++i) {
    for(size_t j = 0; j < m; ++j) {
      out[i*m + j] = mat[i][j];
    }
  }
}

typedef Eigen::Map<Eigen::Matrix<int, Eigen::Dynamic,
                                 Eigen::Dynamic, Eigen::RowMajor> > MapMatInt;
typedef Eigen::Matrix<int, Eigen::Dynamic,
                      Eigen::Dynamic, Eigen::RowMajor> MatInt;
typedef Eigen::Ref<MatInt > MatI;
typedef Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic,
                                 Eigen::Dynamic, Eigen::RowMajor> > MapMatFloat;
typedef Eigen::Matrix<float, Eigen::Dynamic,
                      Eigen::Dynamic, Eigen::RowMajor> MatFloat;
typedef Eigen::Ref<MatFloat > MatF;

#endif
