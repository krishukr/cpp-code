#include <algorithm>
#include <cstdio>
#include <iostream>

const int MAX_N = 1000050;

struct Node {
    int l;        // left son
    int r;        // right son
    long long v;  // value
    long long t;  // tag
} tree[MAX_N << 2];

struct Que {
    int op;
    int l;
    int r;
    int i;  // index
    long long v;
} q[MAX_N], q1[MAX_N], q2[MAX_N];

long long ans[MAX_N];

#pragma region initial
namespace Tree {

void update(int x);

void pushdown(int x);

void build(int x, int l, int r);

void mod(int x, int l, int r, long long v);

long long query(int x, int l, int r);

}  // namespace Tree

void solve(long long l, long long r, int ql, int qr);

template <typename T>
T read();
#pragma endregion initial

int main() {
    std::ios::sync_with_stdio(false);
    // freopen("lg-P3332.in", "r", stdin);
    // freopen("lg-P3332.out", "w", stdout);

    int n = read<int>(), m = read<int>();
    Tree::build(1, 1, n);

    int tot = 0;
    for (int i = 1; i <= m; i++) {
        q[i].op = read<int>();
        q[i].l = read<int>();
        q[i].r = read<int>();
        q[i].v = read<long long>();
        q[i].i = (q[i].op == 2 ? ++tot : 0);
    }

    solve(-n, n, 1, m);
    for (int i = 1; i <= tot; i++) {
        std::cout << ans[i] << '\n';
    }

    return 0;
}

namespace Tree {

void update(int x) { tree[x].v = tree[x * 2].v + tree[x * 2 + 1].v; }

void pushdown(int x) {
    if (tree[x].t) {
        int mid = (tree[x].l + tree[x].r) / 2;
        tree[x * 2].t += tree[x].t;
        tree[x * 2 + 1].t += tree[x].t;
        tree[x * 2].v += tree[x].t * (mid - tree[x].l + 1);
        tree[x * 2 + 1].v += tree[x].t * (tree[x].r - mid);
        tree[x].t = 0;
    }
}

void build(int x, int l, int r) {
    tree[x].l = l;
    tree[x].r = r;
    tree[x].t = tree[x].v = 0;

    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    Tree::build(x * 2, l, mid);
    Tree::build(x * 2 + 1, mid + 1, r);
    Tree::update(x);
}

void mod(int x, int l, int r, long long v) {
    if (l <= tree[x].l and tree[x].r <= r) {
        tree[x].t += v;
        tree[x].v += v * (tree[x].r - tree[x].l + 1);
        return;
    }
    Tree::pushdown(x);
    int mid = (tree[x].l + tree[x].r) / 2;
    if (l <= mid) {
        Tree::mod(x * 2, l, r, v);
    }
    if (mid < r) {
        Tree::mod(x * 2 + 1, l, r, v);
    }
    Tree::update(x);
}

long long query(int x, int l, int r) {
    if (l <= tree[x].l and tree[x].r <= r) {
        return tree[x].v;
    }
    Tree::pushdown(x);
    int mid = (tree[x].l + tree[x].r) / 2;
    long long res = 0;
    if (l <= mid) {
        res += Tree::query(x * 2, l, r);
    }
    if (mid < r) {
        res += Tree::query(x * 2 + 1, l, r);
    }
    return res;
}

}  // namespace Tree

void solve(long long l, long long r, int ql, int qr) {
    if (l > r or ql > qr) {
        return;
    }
    if (l == r) {
        for (int i = ql; i <= qr; i++) {
            if (q[i].op == 2) {
                ans[q[i].i] = l;
            }
        }
        return;
    }

    long long mid = (l + r) / 2;
    int cnt1 = 0, cnt2 = 0, f1 = 0, f2 = 0;
    for (int i = ql; i <= qr; i++) {
        if (q[i].op == 1) {
            if (q[i].v > mid) {
                Tree::mod(1, q[i].l, q[i].r, 1);
                q1[++cnt1] = q[i];
            } else {
                q2[++cnt2] = q[i];
            }
        } else {
            long long tmp = Tree::query(1, q[i].l, q[i].r);
            if (tmp >= q[i].v) {
                q1[++cnt1] = q[i];
                f2 = 1;
            } else {
                q[i].v -= tmp;
                q2[++cnt2] = q[i];
                f1 = 1;
            }
        }
    }

    for (int i = 1; i <= cnt1; i++) {
        if (q1[i].op == 1 and q1[i].v > mid) {
            Tree::mod(1, q1[i].l, q1[i].r, -1);
        }
    }
    for (int i = ql; i < ql + cnt1; i++) {
        q[i] = q1[i - ql + 1];
    }
    for (int i = ql + cnt1; i <= qr; i++) {
        q[i] = q2[i - ql - cnt1 + 1];
    }

    if (f2) {
        solve(mid + 1, r, ql, ql + cnt1 - 1);
    }
    if (f1) {
        solve(l, mid, ql + cnt1, qr);
    }
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