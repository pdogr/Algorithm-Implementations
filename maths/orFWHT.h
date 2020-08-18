#include <bits/stdc++.h>
using namespace std;
#define LL long long

namespace Convolution {

void orFWHT(vector<LL> &A, bool iv = 0) {  // matrix [1 1][1 0]
  int n = A.size();
  for (int s = 1; s < n; s <<= 1) {
    for (int i = 0; i < n; i += 2 * s) {
      for (int j = 0; j < s; ++j) {
        cd u = A[i + j], v = A[i + j + s];
        if (!iv) {
          A[i + j] = u + v;
          A[i + j + s] = u;
        } else {
          A[i + j] = v;
          A[i + j + s] = u - v;
        }
      }
    }
  }
}

}  // namespace Convolution
