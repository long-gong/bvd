#include "bvd.hpp"
#include <algorithm> // std::random_shuffle
#include <cstdlib>   // std::rand, std::srand
#include <ctime>     // std::time
#include <iostream>  // std::cout
#include <vector>    // std::vector

std::vector<int> random_match(size_t n) {
  std::vector<int> myvector;

  // set some values:
  for (int i = 0; i < (int)n; ++i)
    myvector.push_back(i);

  // using built-in random generator:
  std::random_shuffle(myvector.begin(), myvector.end());

  return myvector;
}

template <typename T> void print_match(const std::vector<T> &match) {
  for (size_t i = 0; i < match.size(); ++i)
    std::cout << "(" << i << ", " << match[i] << ") ";
  std::cout << "\n";
}

std::vector<std::vector<unsigned>> random_doubly_stochatic(size_t n,
                                                           unsigned w) {
  std::vector<std::vector<unsigned>> mat(n, std::vector<unsigned>(n, 0));

  std::cout << "Generating random matches ...\n";
  while (w > 0) {
    auto match = random_match(n);
    std::cout << "\t";
    print_match(match);
    for (size_t i = 0; i < n; ++i)
      ++mat[i][match[i]];
    --w;
  }
  std::cout << "Done\n\n";
  return mat;
}

int main() {
  std::srand(unsigned(std::time(0)));

  unsigned w = 3;
  size_t n = 8;

  std::vector<std::vector<unsigned>> matches;
  birkhoff_von_neumann_decomposition(random_doubly_stochatic(n, w), matches, w);

  std::cout << "Got " << matches.size() << " matchings:\n";
  for (const auto &match : matches) {
    std::cout << "\t";
    print_match(match);
  }

  return 0;
}