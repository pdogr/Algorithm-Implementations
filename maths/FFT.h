#include <bits/stdc++.h>
using namespace std;
#define LL long long

namespace Convolution {

using cd = complex<double>;
const double PI = acos(-1);

int reverse(int n, int lg) {
  int r = 0;
  for (int i = 0; i < lg; ++i) {
    if (n & (1 << i)) r |= 1 << (lg - i - 1);
  }
  return r;
}
void FFT(vector<cd> &A, int iv = 1) {
  int n = A.size();
  int lg = 1;
  while ((1 << lg) < n) ++lg;
  for (int i = 0; i < n; ++i) {
    int rv = reverse(i, lg);
    if (i < rv) swap(A[i], A[rv]);
  }

  for (int s = 1; s < n; s <<= 1) {
    double ang = iv * PI / s;

    cd wi(cos(ang), sin(ang));
    for (int i = 0; i < n; i += 2 * s) {
      cd w(1);
      for (int j = 0; j < s; ++j) {
        cd u = A[i + j], v = A[i + j + s] * w;
        w *= wi;
        A[i + j] = u + v;
        A[i + j + s] = u - v;
      }
    }
  }
  if (iv == -1) {
    for (int i = 0; i < n; ++i) A[i] /= n;
  }
}

}  // namespace Convolution
