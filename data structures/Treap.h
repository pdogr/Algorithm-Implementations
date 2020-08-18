#include <bits/stdc++.h>
using namespace std;

namespace DataStructures {

using LL = long long;
class Treap {
 private:
  mt19937 classRng;
  LL rand(LL l, LL r) {
    return (l + uniform_int_distribution<LL>(0, r - l)(classRng));
  }

  // treap node
  class node {
   public:
    LL val, priority, size;
    node *l, *r;
  };

  using pnode = node *;

  pnode getNode(LL val) {
    pnode p = new node();
    p->val = val;
    p->size = 1;
    p->priority = this->rand(0, 1e7);
    return p;
  }

  int _getSize(pnode t) { return t ? t->size : 0; }
  void _updateSize(pnode t) {
    if (t) t->size = _getSize(t->l) + _getSize(t->r) + 1;
  }

  // splits root into <l,r> according to split
  pair<pnode, pnode> _split(pnode root, LL splitVal) {
    if (!root) {
      return {0, 0};
    }

    pair<pnode, pnode> ret;

    if (root->val <= splitVal) {
      ret = _split(root->r, splitVal);
      root->r = ret.first;
      _updateSize(root);
      return {root, ret.second};
    } else {
      ret = _split(root->l, splitVal);
      root->l = ret.second;
      _updateSize(root);
      return {ret.first, root};
    }
  }

  // merges (l,r) and returns the merged node
  pnode _merge(pnode l, pnode r) {
    if (!l || !r) {
      return l ? l : r;
    } else if (l->priority > r->priority) {
      pnode p = _merge(l->r, r);
      l->r = p;
      _updateSize(l);
      return l;
    } else {
      pnode p = _merge(l, r->l);
      r->l = p;
      _updateSize(r);
      return r;
    }
  }

  pnode _find(pnode root, LL key) {
    if (!root) {
      return 0;
    } else if (root->val == key) {
      return root;
    } else if (root->val >= key) {
      return _find(root->l, key);
    } else {
      return _find(root->r, key);
    }
  }

  void _erase(pnode &root, LL key) {
    if (!root) {
      return;
    } else if (root->val == key) {
      pnode temp = root;
      pnode mergedChildren = _merge(root->l, root->r);
      root = mergedChildren;
      delete (temp);
    } else {
      if (root->val < key) {
        _erase(root->r, key);
      } else {
        _erase(root->l, key);
      }
    }

    _updateSize(root);
  }

  void _insert(pnode &root, pnode it) {
    if (!root) {
      root = it;
    } else if (it->priority > root->priority) {
      pair<pnode, pnode> p = _split(root, it->val);
      it->l = p.first;
      it->r = p.second;
      root = it;
    } else {
      if (root->val < it->val) {
        _insert(root->r, it);
      } else {
        _insert(root->l, it);
      }
    }

    _updateSize(root);
  }

 public:
  pnode root;
  Treap() : root(0) {
    classRng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
  }

  void insert(LL key) {
    pnode p = getNode(key);
    _insert(root, p);
  }

  void erase(LL key) { _erase(root, key); }

  pnode unite(pnode l, pnode r) {
    if (!l || !r) {
      return l ? l : r;
    }

    if (l->priority < r->priority) {
      swap(l, r);
    }

    pair<pnode, pnode> p = _split(r, l->val);
    l->l = unite(l->l, p.first);
    l->r = unite(l->r, p.second);
    return l;
  }

  pnode find(LL key) { return _find(root, key); }
};
};  // namespace DataStructures