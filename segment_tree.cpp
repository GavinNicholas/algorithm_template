#include <iostream>
#include <algorithm>
#include <string>
#include <climits>
#include <vector>
#include <cstdio>
#include <cstring>

namespace segment_tree {
    const int MAXN = 100000 + 5;
    struct Node {
        Node *lc, *rc;
        int l, r, lazy_add, lazy_set, min, max, sum;
        bool lazy_set_exist;
        void clear() {
            l = r = 0;
            sum = lazy_add = min = max = lazy_set = 0;
            lazy_set_exist = false;
            lc = rc = NULL;
        }
    };
    struct Tree {
        #define mid (root->l + root->r) >> 1
        Node *root, *cur;
        int a[MAXN];
        Node pool[MAXN * 4];
		void init() {
			cur = pool;
			cur->clear();
			root = cur++;
		}
		Node *newnode() {
			cur->clear();
			return cur++;
		}
        void addTag_add(Node *root, int delta) {
            root->max += delta;   root->min += delta;
            root->sum += (root->r - root->l) * delta;
            root->lazy_add += delta;
        }
        void addTag_set(Node *root, int value) {
            root->max = root->min = value;
            root->sum = (root->r - root->l) * value;
            root->lazy_set = value;
            root->lazy_set_exist = true;
            root->lazy_add = 0;
        }
        void pushDown(Node *root) {
            if (root->lazy_add) {
                addTag_add(root->lc, root->lazy_add);
                addTag_add(root->rc, root->lazy_add);
                root->lazy_add = 0;
            }
            if (root->lazy_set_exist) {
                addTag_set(root->lc, root->lazy_set);
                addTag_set(root->rc, root->lazy_set);
                root->lazy_set_exist = false;
            }
        }
        void update(Node *root) {
            root->sum = root->lc->sum + root->rc->sum;
            root->min = std::min(root->lc->min, root->rc->min);
            root->max = std::max(root->lc->max, root->rc->max);
        }
        void build(Node *root, int l, int r) {
            root->l = l;    root->r = r;
            if (r - l == 1) {
                root->min = root->max = root->sum = a[l];
                return;
            }
            int tmp = (l + r) >> 1;
            root->lc = newnode();   build(root->lc, l, tmp);
            root->rc = newnode();   build(root->rc, tmp, r);
            update(root);
        }
        void modify_add(Node *root, int pos, int delta) {
            if (root->r - root->l == 1) {
                root->sum += delta;
                root->min += delta;
                root->max += delta;
            }
            else {
                if (pos < mid) modify_add(root->lc, pos, delta);
                else modify_add(root->rc, pos, delta);
                update(root);
            }
        }
        void modify_add(Node *root, int l, int r, int delta) {
            if (root->l >= l && root->r <= r) addTag_add(root, delta);
            else {
                pushDown(root);
                if (l < mid) modify_add(root->lc, l, std::min(mid, r), delta);
                if (r > mid) modify_add(root->rc, std::max(mid, l), r, delta);
                update(root);
            }
        }
        void modify_set(Node *root, int pos, int value) {
            if (root->r - root->l == 1) {
                root->sum = root->min = root->max = value;
            }
            else {
                if (pos < mid) modify_set(root->lc, pos, value);
                else modify_set(root->rc, pos, value);
                update(root);
            }
        }
        void modify_set(Node *root, int l, int r, int value) {
            if (root->l >= l && root->r <= r) addTag_set(root, value);
            else {
                pushDown(root);
                if (l < mid) modify_set(root->lc, l, std::min(mid, r), value);
                if (r > mid) modify_set(root->rc, std::max(mid, l), r, value);
                update(root);
            }
        }
        int query(Node *root, int pos) {
            if (root->r - root->l == 1) return root->sum;
            else {
                pushDown(root);
                if (pos < mid) return query(root->lc, pos);
                else return query(root->rc, pos);
            }
        }
        int query_sum(Node *root, int l, int r) {
            if (root->l >= l && root->r <= r) return root->sum;
            else {
                pushDown(root);
                int ans = 0;
                if (l < mid) ans += query_sum(root->lc, l, std::min(mid, r));
                if (r > mid) ans += query_sum(root->rc, std::max(mid, l), r);
                return ans;
            }
        }
        int query_max(Node *root, int l, int r) {
            if (root->l >= l && root->r <= r) return root->max;
            else {
                pushDown(root);
                int ans = INT_MIN;
                if (l < mid) ans = std::max(ans, query_max(root->lc, l, std::min(mid, r)));
                if (r > mid) ans = std::max(ans, query_max(root->rc, std::max(l, mid), r));
                return ans;
            }
        }
        int query_min(Node *root, int l, int r) {
            if (root->l >= l && root->r <= r) return root->min;
            else {
                pushDown(root);
                int ans = INT_MAX;
                if (l < mid) ans = std::min(ans, query_min(root->lc, l, std::min(mid, r)));
                if (r > mid) ans = std::min(ans, query_min(root->rc, std::max(mid, l), r));
                return ans;
            }
        }
        #undef mid
    };
}

using namespace segment_tree;
using namespace std;

Tree tree;
int n;

inline void init() {
	tree.init();
	for (int i = 1; i <= n; i++) tree.a[i] = -1;
}