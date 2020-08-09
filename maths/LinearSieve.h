#include<bits/stdc++.h>
using namespace std;

//https://codeforces.com/blog/entry/54090
namespace LinearSieve {

vector<int> GetPrimes(int M) {
	vector<int> prime;
	vector<bool> ic;
	ic.resize(M);

	for (int i = 2; i < M; ++i) {
		if (!ic[i]) {
			prime.push_back(i);
		}

		for (int j = 0; j < prime.size() && i * prime[j] < M; ++j) {
			ic[i * prime[j]] = 1;
			if (i % prime[j] == 0) {
				break;
			}
		}
	}

	return prime;
}

vector<int> GetMu(int M) {

	// Idea can be extended to any multiplicative function by maintaining freq of spf
	vector<int> prime, freq, mu;
	freq.resize(M);
	mu.resize(M, 1);
	vector<bool> ic;
	ic.resize(M);

	for (int i = 2; i < M; ++i) {
		if (!ic[i]) {
			prime.push_back(i);
			freq[i] = 1;
		}

		for (int j = 0; j < prime.size() && i * prime[j] < M; ++j) {
			ic[i * prime[j]] = 1;
			if (i % prime[j] == 0) {
				freq[i * prime[j]] = 1 + freq[i];
				mu[i * prime[j]] = 0;
				break;

			}
			else {
				freq[i * prime[j]] = 1;
				mu[i * prime[j]] = -1 * mu[i];
			}
		}
	}

	return mu;
}

};
