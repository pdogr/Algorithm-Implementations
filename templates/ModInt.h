#include <bits/stdc++.h>
using namespace std;
#define LL long long

namespace templates {

template <LL MOD>
class ModInt {  // usage ModInt<1e9+7> a(0);
 public:
  static LL pw(LL a, LL b) {
    LL ans = 1;
    while (b) {
      while (!(b & 1)) b >>= 1, a = (a * a) % MOD;
      ans = (ans * a) % MOD, --b;
    }
    return ans;
  }
  LL x;
  ModInt() : x(0) {}
  ModInt(LL x) : x(x % MOD) {}
  ModInt operator+(ModInt b) {
    ModInt ans;
    ans.x = x + b.x;
    if (ans.x >= MOD) ans.x -= MOD;
    return ans;
  }
  ModInt &operator+=(ModInt b) {
    x += b.x;
    if (x >= MOD) x -= MOD;
    return *this;
  }
  ModInt operator-(ModInt b) {
    ModInt ans;
    ans.x = x - b.x;
    if (ans.x < 0) ans.x += MOD;
    return ans;
  }
  ModInt &operator-=(ModInt b) {
    x -= b.x;
    if (x < 0) x += MOD;
    return *this;
  }
  ModInt operator-() {
    ModInt ans;
    if (x == 0) return ans;
    ans.x = MOD - x;
    return ans;
  }
  ModInt operator*(ModInt b) { return ModInt(x * b.x); }
  ModInt &operator*=(ModInt b) {
    x = (x * b.x) % MOD;
    return *this;
  }
  ModInt inv() {
    if (MOD >= 2) return ModInt(pw(x, MOD - 2));
    return ModInt();
  }
  ModInt operator/(ModInt b) { return ModInt(x * b.inv().x); }
  ModInt &operator/=(ModInt b) {
    x = (x * b.inv().x) % MOD;
    return *this;
  }
  bool operator==(ModInt b) { return x == b.x; }
  bool operator!=(ModInt b) { return x != b.x; }
};

}  // namespace templates