#ifndef _UTILS_HPP_
#define _UTILS_HPP_
#include <algorithm>
#include <functional>
#include <utility>
#include <vector>

template <typename matrix>
inline unsigned cal_row_sum(const matrix &mat, size_t row_id) {
  unsigned row_sum = 0;
  for (size_t i = 0; i < (size_t)mat.cols(); ++i) row_sum += mat(row_id, i);
  return row_sum;
}

template <typename matrix>
inline unsigned cal_col_sum(const matrix &mat, size_t col_id) {
  unsigned col_sum = 0;
  for (size_t i = 0; i < (size_t)mat.rows(); ++i) col_sum += mat(i, col_id);
  return col_sum;
}

template <typename matrix>
inline bool check_doubly_stochastic(matrix &mat, unsigned w = (size_t)-1) {
  if (mat.rows() != mat.cols()) return false;
  size_t rs = 1;
  if (w == (size_t)-1)
    w = cal_row_sum(mat, 0);
  else
    rs = 0;
  for (size_t row_id = rs; row_id < (size_t)mat.rows(); ++row_id) {
    if (cal_row_sum(mat, row_id) != w) return false;
  }
  for (size_t col_id = 0; col_id < (size_t)mat.cols(); ++col_id) {
    if (cal_col_sum(mat, col_id) != w) return false;
  }
  return true;
}

template <typename matrix>
inline void padding_to_doubly_stochastic(
    matrix &mat,                          // non-negative square matrix
    unsigned w,                           // maximum row sum or col sum
    std::vector<unsigned> row_sums = {},  // sums of each row
    std::vector<unsigned> col_sums = {}   // sums of each column
) {
  const size_t m = mat.rows();
  if (m == 0) return;

  if (m != (size_t)mat.cols())
    throw std::logic_error("Input matrix MUST be a square matrix!");

#ifdef DEBUG
  printf("m = %lu\n", m);
#endif
  std::vector<std::pair<unsigned, size_t>> row_sum_pairs;
  std::vector<std::pair<unsigned, size_t>> col_sum_pairs;
  if (row_sums.empty()) {
    for (size_t row_id = 0; row_id < m; ++row_id)
      row_sum_pairs.emplace_back(cal_row_sum(mat, row_id), row_id);
  } else {
    for (size_t row_id = 0; row_id < m; ++row_id)
      row_sum_pairs.emplace_back(row_sums[row_id], row_id);
  }
  if (col_sums.empty()) {
    for (size_t col_id = 0; col_id < m; ++col_id)
      col_sum_pairs.emplace_back(cal_col_sum(mat, col_id), col_id);
  } else {
    for (size_t col_id = 0; col_id < m; ++col_id) {
      col_sum_pairs.emplace_back(col_sums[col_id], col_id);
    }
  }

  std::make_heap(row_sum_pairs.begin(), row_sum_pairs.end());
  std::make_heap(col_sum_pairs.begin(), col_sum_pairs.end());

  while (!row_sum_pairs.empty() && !col_sum_pairs.empty()) {
    std::pop_heap(row_sum_pairs.begin(), row_sum_pairs.end());
    std::pop_heap(col_sum_pairs.begin(), col_sum_pairs.end());
    auto r_top = row_sum_pairs.back();
    auto c_top = col_sum_pairs.back();

    row_sum_pairs.pop_back();
    col_sum_pairs.pop_back();
    if (r_top.first >= c_top.first) {
      if (r_top.first < w) {
        auto delta = w - r_top.first;
#ifdef DEBUG
        printf("r = %lu, c = %lu, delta = %u\n", r_top.second, c_top.second,
               delta);
#endif
        mat(r_top.second, c_top.second) += delta;
        c_top.first += delta;
      }
      if (c_top.first < w) {
        col_sum_pairs.push_back(c_top);
        std::push_heap(col_sum_pairs.begin(), col_sum_pairs.end());
      }
    } else {
      if (c_top.first < w) {
        auto delta = w - c_top.first;
        mat(r_top.second, c_top.second) += delta;
        r_top.first += delta;
      }
      if (r_top.first < w) {
        row_sum_pairs.push_back(r_top);
        std::push_heap(row_sum_pairs.begin(), row_sum_pairs.end());
      }
    }
  }
}

#endif  // _UTILS_HPP_