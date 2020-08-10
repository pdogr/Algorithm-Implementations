#include<bits/stdc++.h>
using namespace std;


namespace DataStructures {

//Credits: Tourist
// usage SparseTable<int>(vector<int> v,[](int a,int b){return a+b;})
template<typename T, class F = function<T(T&, T&)>>
class SparseTable {
public:
	int n;
	vector<vector<T>> up;
	F func;

	SparseTable(vector<T> &v, F f): func(f) {
		n = a.size();
		int max_log = 32 - __builtin_clz(n);
		up.resize(max_log);
		up[0] = a;
		for (int j = 1; j < max_log; ++j) {
			up[j].resize(n - (1 << j) + 1);
			for (int i = 0; i <= (n - (1 << j)); ++i) {
				up[j][i] = func(up[j - 1][i], up[j - 1][i + (1 << (j - 1))]);
			}
		}
	}

	T get(int l, int r) {
		if (l > r)return T(0);
		int lg = 32 - __builtin_clz(r - l + 1) - 1;
		return func(up[lg][l], up[lg][r - (1 << lg) + 1]);
	}
};
};