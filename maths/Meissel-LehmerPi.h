#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

namespace PrimeCounting {

namespace MeisselLehmer {
using LL = long long;
const int M1 = 100011;
const int M2 = 211;
const int MM = 10000011;
vector<LL> prime, pi;
vector<bool> ic;
vector<vector<LL>> dp;

void init() {
  pi.resize(MM);
  ic.resize(MM);
  for (int i = 2; i < MM; ++i) {
    if (!ic[i]) {
      prime.push_back(i);
      pi[i] = 1;
    }

    pi[i] += pi[i - 1];
    for (int j = 0; j < prime.size() and i * prime[j] < MM; ++j) {
      ic[i * prime[j]] = 1;
      if (i % prime[j] == 0) break;
    }
  }
  dp.resize(M2);
  for (int i = 0; i < M2; ++i) {
    dp[i].resize(M1);
    for (int j = 0; j < M1; ++j) {
      if (!i) {
        dp[i][j] = j;
      } else {
        dp[i][j] = dp[i - 1][j] - dp[i - 1][j / prime[i - 1]];
      }
    }
  }
}

LL Phi(LL x, LL a) {
  if (!a) return x;
  if (!x) return 0;
  LL p = prime[a - 1];
  if (x < p) return 1;
  if (x < M1 and a < M2) return dp[a][x];
  return Phi(x, a - 1) - Phi(x / p, a - 1);
}

LL Pi(LL M) {
  if (M < MM) return pi[M];
  LL r3 = cbrt(M + 0.2);
  LL r2 = sqrt(M + 0.2);
  LL a = Pi(r3);
  LL S = Phi(M, a) + a - 1;
  for (int i = a; prime[i] <= r2; ++i) {
    S = S - (Pi(M / prime[i]) - Pi(prime[i]) + 1);
  }
  return S;
}
}  // namespace MeisselLehmer
}  // namespace PrimeCounting