#include<bits/stdc++.h>
using namespace std;

namespace DataStructures {

// usage BIT<int>(sz,[](int a,int b){return a+b;})
template<typename T, class F = function<T(T&, T&)>>
class BIT {
public:
	int n;
	vector<T> B;
	F func;
	BIT(int sz, F f): func(f) {
		n = sz;
		B = vector<T>(n + 1);
	}

	void update(int x, T y) {
		for (; x <= n; x += x & -x) {
			B[x] = func(B[x], y);
		}
	}

	T sum(int x) {
		T s(0);
		for (; x >= 1; x -= x & -x) {
			s = func(s, B[x]);
		}

		return s;
	}

};
};