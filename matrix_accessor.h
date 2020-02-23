#ifndef _MATRIX_ACCESSOR_H_
#define _MATRIX_ACCESSOR_H_
#include <vector>

template <typename T> class DenseMatrix {
public:
  DenseMatrix(size_t m, size_t n) : data_(m, std::vector<T>(n, 0)) {}
  DenseMatrix(std::vector<std::vector<T>> data) : data_(std::move(data)) {}
  T &operator()(size_t i, size_t j) { return data_[i][j]; }
  const T &operator()(size_t i, size_t j) const { return data_[i][j]; }
  size_t rows() const { return data_.size(); }
  size_t cols() const { return (data_.empty() ? 0 : data_.front().size()); }

private:
  std::vector<std::vector<T>> data_;
}; // DenseMatrix


#endif // _MATRIX_ACCESSOR_H_