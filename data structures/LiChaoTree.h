#include <bits/stdc++.h>
using namespace std;

namespace DataStructures {

using LL = long long;
const LL Inf = 3e18;

class LCT {
 public:
  // Denotes line of form y=ax+b
  class Line {
   public:
    LL a, b;
    Line() : a(0), b(-Inf) {}
    Line(LL _a, LL _b) : a(_a), b(_b) {}
    LL operator()(LL x) { return a * x + b; }
  };

  // Denotes a node in LCT
  class Node {
   public:
    LL xl, xr;  // define the range for  which curnode is valid
    Node *l, *r;
    Line la;
    Node() : l(0), r(0) {}
  };

  Node* get(LL xl, LL xr) {
    Node* n = new Node();
    n->xl = xl;
    n->xr = xr;
    n->la = Line();
    return n;
  }

  Node* t;

  LCT(LL xMinLimit = -1e9, LL xMaxLimit = 1e9) {  // range limit of x
    t = get(xMinLimit, xMaxLimit);
  }

  void insert(LL a, LL b, Node*& c) {
    Line nl(a, b);

    LL xl = c->xl, xr = c->xr;
    LL xm = (xl + xr) >> 1;

    Line low = c->la, high = nl;

    if (low(xl) > high(xl)) {
      swap(low, high);
    }

    if (low(xr) <= high(xr)) {
      c->la = high;
      return;
    } else if (low(xm) < high(xm)) {
      c->la = high;

      if (!c->r) {
        c->r = get(xm + 1, xr);
      }

      insert(low.a, low.b, c->r);
    } else {
      c->la = low;

      if (!c->l) {
        c->l = get(xl, xm);
      }

      insert(high.a, high.b, c->l);
    }
  }

  LL get(LL xq, Node*& c) {
    if (!c) {
      return -Inf;
    }

    LL xl = c->xl, xr = c->xr;
    LL xm = (xl + xr) >> 1;

    if (xq <= xm) {
      return max(c->la(xq), get(xq, c->l));
    } else {
      return max(c->la(xq), get(xq, c->r));
    }
  }
};

};  // namespace DataStructures