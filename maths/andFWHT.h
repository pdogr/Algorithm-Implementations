#include <bits/stdc++.h>
using namespace std;
#define LL long long

namespace Convolution {

void andFWHT(vector<LL> &A, bool iv = 0) {  // matrix [0 1][1 1]
  int n = A.size();
  for (int s = 1; s < n; s <<= 1) {
    for (int i = 0; i < n; i += 2 * s) {
      for (int j = 0; j < s; ++j) {
        cd u = A[i + j], v = A[i + j + s];
        if (!iv) {
          A[i + j] = v;
          A[i + j + s] = u + v;
        } else {
          A[i + j] = v - u;
          A[i + j + s] = v;
        }
      }
    }
  }
}

}  // namespace Convolution
