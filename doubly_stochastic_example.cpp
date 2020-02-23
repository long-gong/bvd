#include <chrono>
#include <eigen3/Eigen/Dense>
#include <iostream>
#include <random>

#include "utils.hpp"

using namespace Eigen;
using namespace std;

using MatrixXu = Matrix<unsigned, Dynamic, Dynamic>;

int main() {
  std::random_device
      rd;  // Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd());  // Standard mersenne_twister_engine seeded with rd()

  unsigned w = 4;
  std::uniform_int_distribution<> dis(0, w);
  MatrixXu mat(8, 8);
  for (size_t i = 0; i < (size_t)mat.rows(); ++i)
    for (size_t j = 0; j < (size_t)mat.cols(); ++j) mat(i, j) = dis(gen);

  std::vector<unsigned> row_sums, col_sums;
  for (size_t i = 0; i < (size_t)mat.rows(); ++i) {
    row_sums.push_back(cal_row_sum(mat, i));
  }
  for (size_t i = 0; i < (size_t)mat.cols(); ++i)
    col_sums.push_back(cal_col_sum(mat, i));

  w = std::max(*std::max_element(row_sums.cbegin(), row_sums.cend()),
               *std::max_element(col_sums.cbegin(), col_sums.cend()));
  std::cout << "Before: mat = \n" << mat << "\n";
  std::cout << "\nw = " << w << "\n\n";

  padding_to_doubly_stochastic(mat, w, row_sums, col_sums);

  std::cout << "After: mat = \n" << mat << "\n";

  std::cout << "Is it a doubly stochastic matrix "
            << check_doubly_stochastic(mat, w) << std::endl;

  return 0;
}