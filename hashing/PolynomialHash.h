#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

using ULL = unsigned long long;

namespace Hashing {

int _gen_base(const int before, const int after) {
  auto seed =
      std::chrono::high_resolution_clock::now().time_since_epoch().count();
  seed ^= ULL(new ULL);
  std::mt19937 mt_rand(seed);
  int base = std::uniform_int_distribution<int>(before + 1, after)(mt_rand);
  return base % 2 == 0 ? base - 1 : base;
}

// usage
// int PolyHash::base(0);
// vector<int> PolyHash::pow1{1};
// vector<ULL> PolyHash::pow1{1};
// PolyHash::base=_gen_base(256, 2147483647);
//
class PolyHash {
 public:
  static vector<int> pow1;
  static vector<ULL> pow2;
  static int base;         // base 1, base 2 is 2^64
  std::vector<int> pref1;  // Hash on prefix modulo mod
  std::vector<ULL> pref2;  // Hash on prefix modulo 2^64
  static inline int diff(int a, int b) {
    // Diff between `a` and `b` modulo mod (0 <= a < mod, 0 <= b < mod)
    return (a -= b) < 0 ? a + 2147483647 : a;
  }
  static inline int mod(ULL x) {
    // Ull -> int
    x += 2147483647;
    x = (x >> 31) + (x & 2147483647);
    return int((x >> 31) + (x & 2147483647));
  }
  inline int get_pow1(int p) const {
    static int __base[4] = {1, base, mod(ULL(base) * base),
                            mod(mod(ULL(base) * base) * ULL(base))};
    return mod(ULL(__base[p % 4]) * pow1[p / 4]);
  }
  inline ULL get_pow2(int p) const {
    static ULL __base[4] = {ULL(1), ULL(base), ULL(base) * base,
                            ULL(base) * base * base};
    return pow2[p / 4] * __base[p % 4];
  }
  PolyHash(const std::string& s)
      : pref1(s.size() + 1u, 0), pref2(s.size() + 1u, 0) {
    const int n = s.size();

    pow1.reserve((n + 3) / 4);
    pow2.reserve((n + 3) / 4);

    // Firstly calculated needed power of base:
    int pow1_4 = mod(ULL(base) * base);  // base^2 mod 2^31-1
    pow1_4 = mod(ULL(pow1_4) * pow1_4);  // base^4 mod 2^31-1
    ULL pow2_4 = ULL(base) * base;       // base^2 mod 2^64
    pow2_4 *= pow2_4;                    // base^4 mod 2^64
    while (4 * (int)pow1.size() <= n) {
      pow1.push_back(mod((ULL)pow1.back() * pow1_4));
      pow2.push_back(pow2.back() * pow2_4);
    }

    int curr_pow1 = 1;
    ULL curr_pow2 = 1;
    for (int i = 0; i < n; ++i) {
      // Fill arrays with polynomial hashes on prefix
      assert(base > s[i]);
      pref1[i + 1] = mod(pref1[i] + (ULL)s[i] * curr_pow1);
      pref2[i + 1] = pref2[i] + s[i] * curr_pow2;
      curr_pow1 = mod((ULL)curr_pow1 * base);
      curr_pow2 *= base;
    }
  }
  inline std::pair<int, ULL> operator()(const int pos, const int len,
                                        const int mxPow) const {
    int hash1 = pref1[pos + len] - pref1[pos];
    ULL hash2 = pref2[pos + len] - pref2[pos];
    if (hash1 < 0) hash1 += 2147483647;
    if (mxPow != 0) {
      hash1 = mod((ULL)hash1 * get_pow1(mxPow - (pos + len - 1)));
      hash2 *= get_pow2(mxPow - (pos + len - 1));
    }
    return std::make_pair(hash1, hash2);
  }
};

};  // namespace Hashing