#include <algorithm>
#include <cstdio>
#include <iostream>

const int MAX_N = 8000010;

struct Node {
    int lc;
    int rc;
    int sum;
} tree[MAX_N];

int root[MAX_N], a[MAX_N], b[MAX_N];
int top;

#pragma region initial
inline int read();

int make(int l, int r);

int mod(int p, int l, int r, int v);

int query(int u, int v, int l, int r, int k);
#pragma endregion initial

int main() {
    std::ios::sync_with_stdio(false);

    int n = read(), q = read();
    for (int i = 1; i <= n; i++) {
        a[i] = read();
        b[i] = a[i];
    }
    std::sort(b + 1, b + n + 1);
    int m = std::unique(b + 1, b + n + 1) - b - 1;

    root[0] = make(1, m);
    for (int i = 1; i <= n; i++) {
        root[i] = mod(root[i - 1], 1, m,
                      std::lower_bound(b + 1, b + m + 1, a[i]) - b);
    }

    for (int i = 1; i <= q; i++) {
        int x = read(), y = read();
        std::cout << b[query(root[x - 1], root[y], 1, m, (y - x + 1) / 2)]
                  << '\n';
    }

    return 0;
}

int make(int l, int r) {
    int x = ++top;
    int mid = (l + r) / 2;
    if (l < r) {
        tree[x].lc = make(l, mid);
        tree[x].rc = make(mid + 1, r);
    }
    return x;
}

int mod(int p, int l, int r, int v) {
    int x = ++top;
    tree[x].lc = tree[p].lc;
    tree[x].rc = tree[p].rc;
    tree[x].sum = tree[p].sum + 1;
    int mid = (l + r) / 2;
    if (l < r) {
        if (v <= mid) {
            tree[x].lc = mod(tree[p].lc, l, mid, v);
        } else {
            tree[x].rc = mod(tree[p].rc, mid + 1, r, v);
        }
    }
    return x;
}

int query(int u, int v, int l, int r, int k) {
    if (l >= r) {
        return l;
    } else {
        int tmp1 = tree[tree[v].lc].sum - tree[tree[u].lc].sum;
        int tmp2 = tree[tree[v].rc].sum - tree[tree[u].rc].sum;
        int mid = (l + r) / 2;
        if (tmp1 > k) {
            return query(tree[u].lc, tree[v].lc, l, mid, k);
        }
        if (tmp2 > k) {
            return query(tree[u].rc, tree[v].rc, mid + 1, r, k);
        }
        return 0;
    }
}

inline int read() {
    int x = 0, f = 1;
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