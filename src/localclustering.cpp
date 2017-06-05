#include "localclustering.hpp"
#include "matrix.hpp"
#include "parameter.hpp"

#include <limits>
#include <cstddef>
#include <functional>

void estimate_S(MatF X, MatI S, MatF A,
                int idx,
                struct ParamLocClust& p,
                std::function<float(float, float)> dist) {

  auto graph_s_i_cost = Row<float>(p.k);
  auto p_graph_s_i_cost = &graph_s_i_cost;
  auto graph_s_i_cost_new = Row<float>(p.k);
  auto p_graph_s_i_cost_new = &graph_s_i_cost_new;

  size_t m = X.cols();
  MatInt graph_s_i_path(p.k, m);

  float min = std::numeric_limits<float>::max();
  int min_idx = 0;

  for(int l = 0; l < p.k; ++l) {
    float cost = dist(X(idx, 0), A(l, 0));
    graph_s_i_cost[l] = cost;
    if(cost < min) {
      min = cost;
      min_idx = l;
    }
  }

  for(size_t j = 1; j < m; ++j) {
    float new_min = std::numeric_limits<float>::max();
    int new_min_idx = 0;

    auto tmp = p_graph_s_i_cost_new;
    p_graph_s_i_cost_new = p_graph_s_i_cost;
    p_graph_s_i_cost = tmp;

    for(int l = 0; l < p.k; ++l) {
      // stay in the same cluster
      if(l == min_idx) {
        (*p_graph_s_i_cost_new)[l] =  min + dist(X(idx,j), A(l,j));
        graph_s_i_path(l,j) = l;
      } else {
        float cost_jump = min + p.lambda + dist(X(idx,j), A(l,j));
        float cost_no_jump = (*p_graph_s_i_cost)[l] + dist(X(idx,j), A(l,j));
        if(cost_jump > cost_no_jump) {
          (*p_graph_s_i_cost_new)[l] = cost_no_jump;
          graph_s_i_path(l,j) = l;
        } else {
          (*p_graph_s_i_cost_new)[l] = cost_jump;
          graph_s_i_path(l,j) = min_idx;
        }
      }
      if((*p_graph_s_i_cost_new)[l] < new_min) {
        new_min = (*p_graph_s_i_cost_new)[l];
        new_min_idx = l;
      }
    }
    min = new_min;
    min_idx = new_min_idx;
  }

  for(int j = m-1; j >= 0; --j) {
    S(idx,j) = min_idx;
    min_idx = graph_s_i_path(min_idx,j);
  }
}

void estimate_A_l2(MatF X, MatI S, MatF A,
                   struct ParamLocClust& p) {
  int n = X.rows();
  int m = X.cols();
  int k = p.k;

  // Mean
  for(int j = 0; j < m; ++j) {
    Row<float> s_k(k, 0);
    for(int l = 0; l < k; ++l) {
      A(l,j) = 0;
    }
    for(int i = 0; i < n; ++i) {
      s_k[S(i,j)]++;
      A(S(i,j),j) += X(i,j);
    }
    for(int l = 0; l < k; ++l) {
      A(l,j) /= s_k[l];
    }
  }
}

void estimate_A_l1(MatF X, MatI S, MatF A,
                   struct ParamLocClust& p) {
  int n = X.rows();
  int m = X.cols();
  int k = p.k;

  // Mean
  for(int j = 0; j < m; ++j) {
    for(int l = 0; l < k; ++l) {
      Row<float> s_i;
      for(int i = 0; i < n; ++i) {
        if(S(i,j) == l) {
          s_i.insert(s_i.begin(),X(i,j));
        }
      }
      if(s_i.size() > 0) {
        A(l,j) = median<float>(s_i);
      }
    }
  }
}

void estimate_A_l0(MatF X, MatI S, MatF A,
                   struct ParamLocClust& p) {
  int n = X.rows();
  int m = X.cols();
  int k = p.k;

  // Mean
  for(int j = 0; j < m; ++j) {
    for(int l = 0; l < k; ++l) {
      Row<float> s_i;
      for(int i = 0; i < n; ++i) {
        if(S(i,j) == l) {
          s_i.insert(s_i.begin(),X(i,j));
        }
      }
      if(s_i.size() > 0) {
        A(l,j) = mode<float>(s_i);
      }
    }
  }
}

void local_clustering_l2(MatF X, MatI S, MatF A,
                         struct ParamLocClust p) {
  size_t n = X.rows();

  for(int iter = 0; iter < p.nbiter; ++iter) {
    for(size_t i = 0; i < n; ++i) {
      estimate_S(X, S, A,
                 i,
                 p,
                 [](float a, float b){return (a - b)*(a - b);});
    }
    estimate_A_l2(X, S, A,
                  p);
  }
}

void local_clustering_l1(MatF X, MatI S, MatF A,
                        struct ParamLocClust p) {
  size_t n = X.rows();

  for(int iter = 0; iter < p.nbiter; ++iter) {
    for(size_t i = 0; i < n; ++i) {
      estimate_S(X, S, A,
                 i,
                 p,
                 [](float a, float b){return (a - b) > 0 ? (a - b) : (b - a);});
    }
    estimate_A_l1(X, S, A,
                  p);
  }
}

void local_clustering_l0(MatF X, MatI S, MatF A,
                         struct ParamLocClust p) {
  size_t n = X.rows();

  for(int iter = 0; iter < p.nbiter; ++iter) {
    for(size_t i = 0; i < n; ++i) {
      estimate_S(X, S, A,
                 i,
                 p,
                 [](float a, float b){return (a == b) ? 0 : 1;});
    }
    estimate_A_l0(X, S, A,
                  p);
  }
}
