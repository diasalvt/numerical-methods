#ifndef LOCALCLUSTERING_C_API_H
#define LOCALCLUSTERING_C_API_H

#include <cstddef>

typedef void* cmatrix;

extern "C" {
  void _local_clustering_l2(cmatrix x, cmatrix s, cmatrix a, size_t n, size_t m,
                            int k, float lambda, int nbiter);

  void _local_clustering_l1(cmatrix x, cmatrix s, cmatrix a, size_t n, size_t m,
                            int k, float lambda, int nbiter);

  void _local_clustering_l0(cmatrix x, cmatrix s, cmatrix a, size_t n, size_t m,
                            int k, float lambda, int nbiter);
}

#endif
