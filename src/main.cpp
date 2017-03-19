#include <iostream>

#include "factorization.hpp"
#include "factorization_c_api.h"

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
  return 0;
}
