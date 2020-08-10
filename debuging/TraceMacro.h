#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
using namespace std;

#define TRACE

#ifdef TRACE

#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
template <typename Arg1>
void __f(const char* name, Arg1&& arg1) {
    cerr << name << " : " << arg1 << std::endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args) {
    const char* comma = strchr(names + 1, ','); cerr.write(names, comma - names) << " : " << arg1 << " | "; __f(comma + 1, args...);
}
#else

#define trace(...)

#endif


template<class T> ostream& operator<<(ostream &os, vector<T> V) {
    os << "[ ";
    for (auto v : V) os << v << " ";
    return os << "]";
}
template<class T> ostream& operator<<(ostream &os, set<T> S) {
    os << "{ ";
    for (auto s : S) os << s << " ";
    return os << "}";
}
template<class T> ostream& operator<<(ostream &os, unordered_set<T> S) {
    os << "{ ";
    for (auto s : S) os << s << " ";
    return os << "}";
}
template<class T> ostream& operator << (ostream& os, multiset<T> S) {
    os << "{ ";
    for (auto s : S) os << s << " ";
    return os << "}";
}
template<class L, class R> ostream& operator<<(ostream &os, pair<L, R> P) {
    return os << "(" << P.first << "," << P.second << ")";
}
template<class L, class R> ostream& operator<<(ostream &os, map<L, R> M) {
    os << "{ ";
    for (auto m : M) os << "(" << m.first << ":" << m.second << ") ";
    return os << "}";
}
template<class L, class R, class chash = std::hash<R>> ostream & operator<<(ostream &os, unordered_map<L, R, chash> M) {
    os << "{ ";
    for (auto m : M) os << "(" << m.first << ":" << m.second << ") ";
    return os << "}";
}
template<class L, class R, class chash = std::hash<R> > ostream & operator<<(ostream &os, gp_hash_table<L, R, chash> M) {
    os << "{ ";
    for (auto m : M) os << "(" << m.first << ":" << m.second << ") ";
    return os << "}";
}