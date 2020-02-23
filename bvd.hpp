#ifndef _BVD_HPP_
#define _BVD_HPP_
#include <numeric>
#include <vector>

#include "matrix_accessor.h"
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/max_cardinality_matching.hpp>

// using doubly_stochastic_matrix = std::vector<std::vector<unsigned>>;

template <typename doubly_stochastic_matrix>
void birkhoff_von_neumann_decomposition(
    doubly_stochastic_matrix mat, std::vector<std::vector<unsigned>> &matches,
    int row_sum = -1);

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

} // end namespace

// implementation
template <>
void birkhoff_von_neumann_decomposition(
    std::vector<std::vector<unsigned>> mat,
    std::vector<std::vector<unsigned>> &matches, int row_sum) {
  if (mat.empty())
    return;

  if (row_sum < 0)
    row_sum = std::accumulate(mat.front().cbegin(), mat.front().cend(), (int)0);
  auto n_vertices = mat.size();
  DenseMatrix<unsigned> dmat(std::move(mat));

  auto g = build_graph(dmat);
  matches.clear();

  //   std::vector<graph_traits<my_graph>::vertex_descriptor> mate(n_vertices);
  //   graph_traits<my_graph>::vertex_iterator vi, vi_end;

  std::vector<int> mate(n_vertices * 2);
  while (row_sum > 0) {
    matches.emplace_back(n_vertices, 0);
    auto &new_match = matches.back();
    edmonds_maximum_cardinality_matching(g, &mate[0]);

    unsigned delta = std::numeric_limits<unsigned>::max();
    // for (boost::tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi) {
    for (size_t i = 0; i < n_vertices; ++i) {
      //   size_t i = *vi;
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

#endif // _BVD_HPP_
