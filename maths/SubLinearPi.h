#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

namespace PrimeCounting {

// Sublinear algorithm for calculating prime counting function
using LL = long long;
const int MM = 10000011;

LL Pi(LL M) {
  LL n = sqrt(M + 0.5) + 1;
  vector<int> prime;
  vector<bool> ic;
  ic.resize(n);

  for (int i = 2; i < n; ++i) {
    if (!ic[i]) {
      prime.push_back(i);
    }

    for (int j = 0; j < prime.size() && i * prime[j] < n; ++j) {
      ic[i * prime[j]] = 1;
      if (i % prime[j] == 0) break;
    }
  }

  vector<LL> Ss(MM + 1);
  // use hash table to store values larger than MM
  gp_hash_table<LL, LL> Sb;

  vector<LL> V;

  LL r2 = n - 1;
  for (int i = 1; i <= r2; ++i) {
    V.push_back(M / i);
  }

  for (int i = M / r2 - 1; i >= 1; --i) {
    V.push_back(i);
  }

  for (int i = 0; i < V.size(); ++i) {
    LL v = V[i];
    if (v > MM) {
      Sb[v] = v - 1;
    } else {
      Ss[v] = v - 1;
    }
  }

  for (int i = 0; i < prime.size(); ++i) {
    int p = prime[i];
    if (p > r2) break;
    LL sp = Ss[p - 1];
    for (LL v : V) {
      if (v / p < p) break;
      LL del = (((v / p > MM) ? Sb[v / p] : Ss[v / p]) - sp);
      if (v > MM) {
        Sb[v] -= del;
      } else {
        Ss[v] -= del;
      }
    }
  }

  LL CntOfPrimes = (M > MM) ? Sb[M] : Ss[M];
  return CntOfPrimes;
};
};  // namespace PrimeCounting