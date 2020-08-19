#include <bits/stdc++.h>
using namespace std;

namespace templates {

template <typename T, int _N, int _M = _N>
class Matrix {  // usage: Matrix<T,5,5> A;
  array<T, _M> a[_N];

 public:
  Matrix() {
    for (int i = 0; i < _N; ++i) a[i].fill(T());
  }
  explicit Matrix(T x) {
    for (int i = 0; i < _N; ++i) a[i].fill(0);
    for (int i = 0; i < _N && i < _M; ++i) a[i][i] = x;
  }
  Matrix(initializer_list<std::array<T, _M>> x) {
    assert(x.size() <= _N);
    for (int i = 0; i < x.size(); ++i) a[i] = *(x.begin() + i);
    for (int i = x.size(); i < _N; ++i) a[i].fill(0);
  }
  void print() {
    for (int i = 0; i < _N; ++i) {
      for (int j = 0; j < _M; ++j) cout << a[i][j].x << " ";
      cout << "\n";
    }
  }
  array<T, _M>& operator[](int x) { return a[x]; }
  const array<T, _M>& operator[](int x) const { return a[x]; }
  Matrix operator+(const Matrix& x) {
    Matrix ans = *this;
    for (int i = 0; i < _N; ++i)
      for (int j = 0; j < _M; ++j) ans[i][j] += x[i][j];
    return ans;
  }
  Matrix& operator+=(const Matrix& x) {
    for (int i = 0; i < _N; ++i)
      for (int j = 0; j < _M; ++j) a[i][j] += x[i][j];
    return *this;
  }
  Matrix operator-(const Matrix& x) {
    Matrix ans = *this;
    for (int i = 0; i < _N; ++i)
      for (int j = 0; j < _M; ++j) ans[i][j] -= x[i][j];
    return ans;
  }
  Matrix& operator-=(const Matrix& x) {
    for (int i = 0; i < _N; ++i)
      for (int j = 0; j < _M; ++j) a[i][j] -= x[i][j];
    return *this;
  }
  template <int K>
  Matrix<T, _N, K> operator*(const Matrix<T, _M, K>& x) {
    Matrix<T, _N, K> ans;
    for (int i = 0; i < _N; ++i)
      for (int j = 0; j < _M; ++j) {
        for (int k = 0; k < K; ++k) {
          ans[i][k] += a[i][j] * x[j][k];
        }
      }
    return ans;
  }
  Matrix operator*(T x) {
    Matrix ans = *this;
    for (int i = 0; i < _N; ++i)
      for (int j = 0; j < _M; ++j) ans[i][j] *= x;
    return ans;
  }
  Matrix& operator*=(T x) {
    for (int i = 0; i < _N; ++i)
      for (int j = 0; j < _M; ++j) a[i][j] *= x;
    return *this;
  }
};

}  // namespace templates