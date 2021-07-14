#include <cmath>
#include <cstdio>
#include <iostream>

const int MAX_N = 100050;

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

void mod(int x, int l, int r);

long long query(int x, int l, int r);

template <typename T>
T read();
#pragma endregion initial

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        a[i] = read<long long>();
    }
    create(1, 1, n);

    int m = read<int>();
    for (int i = 1; i <= m; i++) {
        int op = read<int>(), l = read<int>(), r = read<int>();
        if (op) {
            std::cout << query(1, std::min(l, r), std::max(l, r)) << '\n';
        } else {
            mod(1, std::min(l, r), std::max(l, r));
        }
    }

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

void mod(int x, int l, int r) {
    if (tree[x].lc == tree[x].rc) {
        tree[x].v = sqrt(tree[x].v);
        tree[x].s = sqrt(tree[x].s);
    } else {
        int mid = (tree[x].lc + tree[x].rc) / 2;
        if (l <= mid and tree[x * 2].s > 1) {
            mod(x * 2, l, r);
        }
        if (mid < r and tree[x * 2 + 1].s > 1) {
            mod(x * 2 + 1, l, r);
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