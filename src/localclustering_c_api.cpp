#include <exception>
#include <cstddef>

#include "localclustering_c_api.h"
#include "matrix.hpp"
#include "parameter.hpp"
#include "localclustering.hpp"

void _local_clustering_l2(cmatrix x, cmatrix s, cmatrix a, size_t n, size_t m,
                          int k, float lambda, int nbiter) {
  try {
    auto p_x = (float *)x;
    auto p_s = (int *)s;
    auto p_a = (float *)a;

    MapMatFloat X(p_x, n, m);
    MapMatInt S(p_s, n, m);
    MapMatFloat A(p_a, k, m);

    struct ParamLocClust p;
    p.k = k;
    p.lambda = lambda;
    p.nbiter = nbiter;

    local_clustering_l2(X, S, A, p);

  } catch (std::exception const& e) {
    std::cout << e.what();
  }
}

void _local_clustering_l1(cmatrix x, cmatrix s, cmatrix a, size_t n, size_t m,
                          int k, float lambda, int nbiter) {
  try {
    auto p_x = (float *)x;
    auto p_s = (int *)s;
    auto p_a = (float *)a;

    MapMatFloat X(p_x, n, m);
    MapMatInt S(p_s, n, m);
    MapMatFloat A(p_a, k, m);

    struct ParamLocClust p;
    p.k = k;
    p.lambda = lambda;
    p.nbiter = nbiter;

    local_clustering_l1(X, S, A, p);

  } catch (std::exception const& e) {
    std::cout << e.what();
  }
}

void _local_clustering_l0(cmatrix x, cmatrix s, cmatrix a, size_t n, size_t m,
                          int k, float lambda, int nbiter) {
  try {
    auto p_x = (float *)x;
    auto p_s = (int *)s;
    auto p_a = (float *)a;

    MapMatFloat X(p_x, n, m);
    MapMatInt S(p_s, n, m);
    MapMatFloat A(p_a, k, m);

    struct ParamLocClust p;
    p.k = k;
    p.lambda = lambda;
    p.nbiter = nbiter;

    local_clustering_l0(X, S, A, p);

  } catch (std::exception const& e) {
    std::cout << e.what();
  }
}
