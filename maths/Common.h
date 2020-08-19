#include <bits/stdc++.h>

#include "LinearSieve.h"
using namespace std;
#define LL long long

namespace NT {

LL gcd(LL a, LL b) {
  if (!b) return a;
  return gcd(b, a % b);
}

template <typename T>
T pw(T a, ll b) {
  T ans{1};
  while (b) {
    while (!(b & 1)) b >>= 1, a = (a * a);
    ans = (ans * a), --b;
  }
  return ans;
}

LL powmod(LL a, LL b, LL mod) {
  LL r = 1;
  while (b) {
    if (b & 1) {
      r = r * a % mod;
      r %= mod;
    }
    a = a * a % mod;
    a %= mod;
    b /= 2;
  }
  return r;
}

tuple<LL, LL, LL> extendedEuclid(LL a, LL b) {
  if (!b) {
    return make_tuple(1, 0, a);
  }
  auto [x1, y1, g] = extendedEuclid(b, a % b);
  LL x = y1;
  LL y = x1 - y1 * (a / b);
  return make_tuple(x, y, g);
}

vector<int> prime;
void generatorInit(LL M) { prime = GetPrimes(M); }

LL generator(LL M) {
  vector<LL> f;
  LL n = M;
  LL phi = n;
  for (auto &p : prime) {
    if (p > n) break;
    if (n % p == 0) {
      phi /= p;
      phi *= p - 1;
      while (n % p == 0) n /= p;
    }
  }
  if (n > 1) {
    phi /= n;
    phi *= n - 1;
  }
  n = phi;
  for (auto &p : prime) {
    if (p > n) break;
    if (n % p == 0) {
      f.push_back(p);
      while (n % p == 0) n /= p;
    }
  }
  if (n > 1) f.push_back(n);

  LL ret = -1;
  for (LL g = 2; g <= M; ++g) {
    bool c = true;
    if (gcd(g, M) > 1) continue;

    for (auto &r : f) {
      LL po = powmod(g, phi / r, M);
      if (powmod(g, phi / r, M) == 1) c = 0;
      if (!c) break;
    }
    if (c) return g;
  }
  return ret;
}

}  // namespace NT
