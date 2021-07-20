#include <cstdio>
#include <iostream>

const int MAX_N = 100050;

namespace Tree {

struct Tree {
    int l;
    int r;
    int s;
    int t;
} tree[MAX_N << 2];

void update(int x);

void pushdown(int x);

void build(int x, int l, int r, int k);

int query(int x, int l, int r);

int point(int x, int k);

void mod(int x, int l, int r, int v);

}  // namespace Tree

int num[MAX_N], op[MAX_N], ql[MAX_N], qr[MAX_N];
int n, m, q;

bool solve(int x);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    n = read<int>(), m = read<int>();
    for (int i = 1; i <= n; i++) {
        num[i] = read<int>();
    }
    for (int i = 1; i <= m; i++) {
        op[i] = read<int>();
        ql[i] = read<int>();
        qr[i] = read<int>();
    }

    int l = 1, r = n, ans = 0;
    q = read<int>();
    while (l <= r) {
        int mid = (l + r) / 2;
        if (solve(mid)) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }

    std::cout << ans << '\n';

    return 0;
}

namespace Tree {

void update(int x) { tree[x].s = tree[x * 2].s + tree[x * 2 + 1].s; }

void pushdown(int x) {
    if (tree[x].t) {
        tree[x * 2].t = tree[x].t;
        tree[x * 2 + 1].t = tree[x].t;
        if (tree[x].t == 1) {
            tree[x * 2].s = tree[x * 2].r - tree[x * 2].l + 1;
            tree[x * 2 + 1].s = tree[x * 2 + 1].r - tree[x * 2 + 1].l + 1;
        } else {
            tree[x * 2].s = 0;
            tree[x * 2 + 1].s = 0;
        }
        tree[x].t = 0;
    }
}

void build(int x, int l, int r, int k) {
    tree[x].l = l;
    tree[x].r = r;

    if (l == r) {
        tree[x].s = num[l] >= k;
        tree[x].t = 0;
    } else {
        int mid = (tree[x].l + tree[x].r) / 2;
        build(x * 2, l, mid, k);
        build(x * 2 + 1, mid + 1, r, k);
        update(x);
        tree[x].t = 0;
    }
}

int query(int x, int l, int r) {
    if (l <= tree[x].l and tree[x].r <= r) {
        return tree[x].s;
    }
    if (r < tree[x].l or tree[x].r < l) {
        return 0;
    }
    pushdown(x);
    int mid = (tree[x].l + tree[x].r) / 2;
    return query(x * 2, l, r) + query(x * 2 + 1, l, r);
}

int point(int x, int k) {
    if (tree[x].l == tree[x].r and tree[x].l == k) {
        return tree[x].s;
    }
    pushdown(x);
    int mid = (tree[x].l + tree[x].r) / 2;
    if (k <= mid) {
        return point(x * 2, k);
    } else {
        return point(x * 2 + 1, k);
    }
}

void mod(int x, int l, int r, int v) {
    if (l <= tree[x].l and tree[x].r <= r) {
        tree[x].s = (tree[x].r - tree[x].l + 1) * v;
        tree[x].t = (v ? 1 : -1);
        return;
    }
    if (r < tree[x].l or tree[x].r < l) {
        return;
    }
    pushdown(x);
    int mid = (tree[x].l + tree[x].r) / 2;
    mod(x * 2, l, r, v);
    mod(x * 2 + 1, l, r, v);
    update(x);
}

}  // namespace Tree

bool solve(int x) {
    Tree::build(1, 1, n, x);
    for (int i = 1; i <= m; i++) {
        int tmp = Tree::query(1, ql[i], qr[i]);
        if (op[i]) {
            Tree::mod(1, ql[i], ql[i] + tmp - 1, 1);
            Tree::mod(1, ql[i] + tmp, qr[i], 0);
        } else {
            Tree::mod(1, qr[i] - tmp + 1, qr[i], 1);
            Tree::mod(1, ql[i], qr[i] - tmp, 0);
        }
    }
    return Tree::point(1, q);
}

template <typename T>
T read() {
    T x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    return x * f;
}