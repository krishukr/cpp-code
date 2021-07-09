#include <cstdio>
#include <iostream>

const int MAX_N = 50000050;

struct Node {
    int lc;
    int rc;
    int val;
} tree[MAX_N];

int root[MAX_N], num[MAX_N];
int top;

#pragma region initial
inline int read();

int add(int x);

int make(int x, int l, int r);

int mod(int x, int l, int r, int a, int v);

int query(int x, int l, int r, int a);
#pragma endregion initial

int main() {
    std::ios::sync_with_stdio(false);

    int n = read(), m = read();
    for (int i = 1; i <= n; i++) {
        num[i] = read();
    }
    root[0] = make(0, 1, n);

    for (int i = 1; i <= m; i++) {
        int v = read(), op = read(), loc = read();
        if (op - 1) {
            std::cout << query(root[v], 1, n, loc) << '\n';
            root[i] = root[v];
        } else {
            int value = read();
            root[i] = mod(root[v], 1, n, loc, value);
        }
    }

    return 0;
}

int add(int x) {
    tree[++top] = tree[x];
    return top;
}

int make(int x, int l, int r) {
    x = ++top;
    if (l == r) {
        tree[x].val = num[l];
        return top;
    } else {
        int mid = (l + r) / 2;
        tree[x].lc = make(tree[x].lc, l, mid);
        tree[x].rc = make(tree[x].rc, mid + 1, r);
        return x;
    }
}

int mod(int x, int l, int r, int a, int v) {
    x = add(x);
    if (l == r) {
        tree[x].val = v;
    } else {
        int mid = (l + r) / 2;
        if (a <= mid) {
            tree[x].lc = mod(tree[x].lc, l, mid, a, v);
        } else {
            tree[x].rc = mod(tree[x].rc, mid + 1, r, a, v);
        }
    }
    return x;
}

int query(int x, int l, int r, int a) {
    if (l == r) {
        return tree[x].val;
    } else {
        int mid = (l + r) / 2;
        if (a <= mid) {
            return query(tree[x].lc, l, mid, a);
        } else {
            return query(tree[x].rc, mid + 1, r, a);
        }
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