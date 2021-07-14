#include <cmath>
#include <cstdio>
#include <iostream>

const int MAX_N = 2000500;

struct Node {
    int lc;
    int rc;
    long long v;
    long long s;
} tree[MAX_N << 2];

long long a[MAX_N];

#pragma region initial
void update(int x);

void create(int x, int l, int r);

void mod(int x, int l, int r, int p);

long long query(int x, int l, int r);

void add(int x, int l, int r, int v);

template <typename T>
T read();
#pragma endregion initial

int main() {
    freopen("tiao.in", "r", stdin);
    freopen("tiao.out", "w", stdout);

    int n = read<int>(), m = read<int>();
    for (int i = 1; i <= n; i++) {
        a[i] = read<long long>();
    }
    create(1, 1, n);

    for (int i = 1; i <= m; i++) {
        int opt = read<int>();
        if (opt == 1) {
            int l = read<int>(), r = read<int>();
            std::cout << query(1, l, r) << '\n';
        }
        if (opt == 2) {
            int l = read<int>(), r = read<int>(), p = read<int>();
            mod(1, l, r, p);
        }
        if (opt == 3) {
            int x = read<int>(), k = read<int>();
            add(1, x, x, k);
        }
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}

void update(int x) {
    tree[x].v = tree[x * 2].v + tree[x * 2 + 1].v;
    tree[x].s = std::max(tree[x * 2].s, tree[x * 2 + 1].s);
}

void create(int x, int l, int r) {
    tree[x].lc = l;
    tree[x].rc = r;
    if (l == r) {
        tree[x].v = tree[x].s = a[l];
    } else {
        int mid = (l + r) / 2;
        create(x * 2, l, mid);
        create(x * 2 + 1, mid + 1, r);
        update(x);
    }
}

void mod(int x, int l, int r, int p) {
    if (l <= tree[x].lc and tree[x].rc <= r and tree[x].s < p) {
        return;
    }
    if (l <= tree[x].lc and tree[x].rc <= r and tree[x].lc == tree[x].rc) {
        tree[x].v %= p;
        tree[x].s %= p;
    } else {
        int mid = (tree[x].lc + tree[x].rc) / 2;
        if (l <= mid) {
            mod(x * 2, l, r, p);
        }
        if (mid < r) {
            mod(x * 2 + 1, l, r, p);
        }
        update(x);
    }
}

void add(int x, int l, int r, int v) {
    if (l == tree[x].lc and r == tree[x].rc) {
        tree[x].s = tree[x].v = v;
    } else {
        int mid = (tree[x].lc + tree[x].rc) / 2;
        if (l <= mid) {
            add(x * 2, l, r, v);
        }
        if (mid < r) {
            add(x * 2 + 1, l, r, v);
        }
        update(x);
    }
}

long long query(int x, int l, int r) {
    if (l <= tree[x].lc and tree[x].rc <= r) {
        return tree[x].v;
    } else {
        long long res = 0;
        int mid = (tree[x].lc + tree[x].rc) / 2;
        if (l <= mid) {
            res += query(x * 2, l, r);
        }
        if (mid < r) {
            res += query(x * 2 + 1, l, r);
        }
        return res;
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