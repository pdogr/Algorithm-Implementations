#include <bits/stdc++.h>
#define LL long long
#define F first
#define S second
#define pb push_back

using namespace std;

namespace NT {

LL BSGS(LL p, LL h, LL g) {
  LL r2 = sqrt(p + 0.7) + 1;
  LL phi = p - 1, i, j;
  using pii = pair<LL, LL>;
  vector<pii> small, big;

  for (j = 0; j < r2; ++j) {
    small.pb({powmod(g, j, p), j});
  }

  LL ee = 0;
  for (i = 0; i * r2 < p; ++i) {
    big.pb({(h * powmod(g, ee, p)) % p, i});
    ee -= r2;
    ee %= phi;
    ee = (ee + phi) % (phi);
  }

  sort(small.begin(), small.end());
  sort(big.begin(), big.end());

  for (auto& s : small) {
    LL x = -1, p = big.size();
    for (; p >= 1; p /= 2) {
      while (x + p < big.size() and big[x + p].F <= s.F) x += p;
    }
    if (x >= 0 and big[x].F == s.F) {
      return big[x].S * r2 + s.S;
    }
  }
  return -1;
}
}  // namespace NT
