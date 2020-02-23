#ifndef _BVD_HPP_
#define _BVD_HPP_
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>
#include <numeric>
#include <stdexcept>
#include <vector>

#include "matrix_accessor.h"

// value of `mat` will be changed in this API. If you won't use it after this API, please move
// your object to this API to avoid unnecessary copy!
//
// throws std::logic_error on failure
template <typename doubly_stochastic_matrix>
void birkhoff_von_neumann_decomposition(
    doubly_stochastic_matrix mat,  // doubly stochatic matrix
    std::vector<std::vector<unsigned>>
        &matches,     // matches after decompositions (return)
    int row_sum = -1  // row sum, -1 ==> need calculation
);

namespace {
using namespace boost;
typedef adjacency_list<vecS, vecS, directedS> my_graph;

template <typename matrix_accessor>
my_graph build_graph(const matrix_accessor &mat) {
  const size_t n_vertices = mat.rows();

  my_graph g(n_vertices);

  for (size_t i = 0; i < n_vertices; ++i) {
    for (size_t j = 0; j < n_vertices; ++j) {
      if (mat(i, j) > 0) {
        add_edge(i, j + n_vertices, g);
      }
    }
  }

  return g;
}

template <typename doubly_stochastic_matrix>
unsigned cal_row_sum(const doubly_stochastic_matrix &mat) {
  unsigned row_sum = 0;
  for (size_t i = 0; i < mat.cols(); ++i) row_sum += mat(0, i);

  return row_sum;
}
}  // end namespace

// implementations
template <typename doubly_stochastic_matrix>
void birkhoff_von_neumann_decomposition(
    doubly_stochastic_matrix dmat, std::vector<std::vector<unsigned>> &matches,
    int row_sum) {
  if (row_sum < 0) cal_row_sum(dmat);

  auto g = build_graph(dmat);
  matches.clear();

  auto n_vertices = dmat.rows();
  std::vector<int> mate(n_vertices * 2);
  while (row_sum > 0) {
    matches.emplace_back(n_vertices, 0);
    auto &new_match = matches.back();
    edmonds_maximum_cardinality_matching(g, &mate[0]);

    unsigned delta = std::numeric_limits<unsigned>::max();
    for (size_t i = 0; i < n_vertices; ++i) {
      size_t j = mate[i] - n_vertices;
#ifdef DEBUG
      printf("mat(%lu, %lu) = %u\n", i, j, dmat(i, j));
#endif
      new_match[i] = j;
      delta = std::min((unsigned)dmat(i, j), delta);
    }
#ifdef DEBUG
    printf("delta = %u\n", delta);
#endif
    if (delta == 0)
      throw std::logic_error("Input matrix is not doubly stochatic");
    // update
    for (size_t i = 0; i < n_vertices; ++i) {
      size_t j = new_match[i];
      dmat(i, j) -= delta;
      if (dmat(i, j) == 0) {
        remove_edge(i, j + n_vertices, g);
      }
    }
    row_sum -= delta;
  }
}

template <>
void birkhoff_von_neumann_decomposition(
    std::vector<std::vector<unsigned>> mat,
    std::vector<std::vector<unsigned>> &matches, int row_sum) {
  if (mat.empty()) return;
  if (row_sum < 0)
    row_sum = std::accumulate(mat.front().cbegin(), mat.front().cend(), (int)0);
  birkhoff_von_neumann_decomposition(DenseMatrix<unsigned>{std::move(mat)},
                                     matches, row_sum);
}

#endif  // _BVD_HPP_
