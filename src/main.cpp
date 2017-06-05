#include <iostream>

#include "matrix.hpp"
#include "factorization.hpp"
#include "factorization_c_api.h"
#include "localclustering.hpp"
#include "localclustering_c_api.h"

int main(){
  Matrix<float> mat = {{6, 3, 4, 8},{3, 6, 5, 1},{4, 5, 10, 7},{8, 1, 7, 25}};

  float in[4][4] = {{6, 3, 4, 8},{3, 6, 5, 1},{4, 5, 10, 7},{8, 1, 7, 25}};
  float out[4][4];

  auto res = cholesky_decomposition(mat);
  for(auto& row: res) {
    for(auto& elem: row) {
      std::cout << elem << " ";
    }
    std::cout << std::endl;
  }

  _cholesky_decomposition(in, out, 4);
  for(auto& row: out) {
    for(auto& elem: row) {
      std::cout << elem << " ";
    }
    std::cout << std::endl;
  }

  float x[4][4] = {{6, 3, 4, 8},{3, 6, 5, 1},{4, 5, 10, 7},{8, 1, 7, 25}};
  int s[4][4] = {{0}};
  float a[2][4] = {{0}};

  MapMatFloat mat_x((float *)x, 4, 4);
  MapMatInt mat_s((int *)s, 4, 4);
  MapMatFloat mat_a((float *)a, 2, 4);

  ParamLocClust p;
  p.k = 2;
  p.lambda = 0.5;

  _local_clustering_l2(x, s, a, 4, 4, 2, 0.5, 10);
  for(int i = 0; i < 4; ++i) {
    for(int j = 0; j < 4; ++j) {
      std::cout << mat_s(i,j) << " ";
    }
    std::cout << std::endl;
  }
  return 0;
}
