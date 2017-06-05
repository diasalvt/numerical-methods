#ifndef LOCALCLUSTERING_HPP
#define LOCALCLUSTERING_HPP

#include "matrix.hpp"
#include "parameter.hpp"

#include <limits>
#include <cstddef>
#include <functional>
#include <vector>

struct ParamLocClust: Parameter<ParamLocClust> {
  int k; // number of clusters
  float lambda; // penalty
  int nbiter; // number of iterations

  ParamLocClust() {
    DECLARE_FIELD(k, ParamLocClust);
    DECLARE_FIELD(lambda, ParamLocClust);
    DECLARE_FIELD(nbiter, ParamLocClust);
  }
};

template <class T>
T median(std::vector<T> &v)
{
  size_t n = v.size() / 2;
  std::nth_element(v.begin(), v.begin()+n, v.end());
  return v[n];
}

template <class T>
T mode(std::vector<T> &v)
{
  std::sort( v.begin(), v.end() );
  T current = v[0];
  T most = v[0];
  int currentCount = 0;
  int mostCount = 0;
  for (auto c : v) {
    if (c == current)
      currentCount++;
    else {
      if (currentCount > mostCount) {
        most = current;
        mostCount = currentCount;
      }
      current = c;
      currentCount = 1;
    }
  }
  return most;
}

void estimate_S(MatF X, MatI S, MatF A,
                int idx,
                struct ParamLocClust& p,
                std::function<float(float, float)> dist);

void estimate_A_l2(MatF X, MatI S, MatF A,
                   struct ParamLocClust& p);

void estimate_A_l1(MatF X, MatI S, MatF A,
                   struct ParamLocClust& p);

void estimate_A_l0(MatF X, MatI S, MatF A,
                   struct ParamLocClust& p);

void local_clustering_l2(MatF X, MatI S, MatF A,
                         struct ParamLocClust p);

void local_clustering_l1(MatF X, MatI S, MatF A,
                         struct ParamLocClust p);

void local_clustering_l0(MatF X, MatI S, MatF A,
                         struct ParamLocClust p);

#endif
