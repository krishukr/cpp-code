#include <cstdio>
#include <iostream>

const int MAX_N = 100050;
int MOD;

struct Node {
    long long v;  // 节点值
    long long m;  // 乘法懒惰标记
    long long a;  // 加法懒惰标记
} tree[MAX_N << 2];

long long a[MAX_N];

#pragma region initial
void update(int x);

void create(int x, int l, int r);

void pushdown(int x, int l, int r);

void multi(int x, int cl, int cr, int l, int r, long long v);

void add(int x, int cl, int cr, int l, int r, long long v);

long long query(int x, int cl, int cr, int l, int r);

template <typename T>
T read();
#pragma endregion initial

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>();
    MOD = read<int>();
    for (int i = 1; i <= n; i++) {
        a[i] = read<long long>();
    }
    create(1, 1, n);

    while (m--) {
        int op = read<int>();
        if (op == 1) {
            int x = read<int>(), y = read<int>();
            long long v = read<long long>();
            multi(1, 1, n, x, y, v);
        }
        if (op == 2) {
            int x = read<int>(), y = read<int>();
            long long v = read<long long>();
            add(1, 1, n, x, y, v);
        }
        if (op == 3) {
            int x = read<int>(), y = read<int>();
            std::cout << query(1, 1, n, x, y) << '\n';
        }
    }

    return 0;
}

void update(int x) { tree[x].v = (tree[x * 2].v + tree[x * 2 + 1].v) % MOD; }

void create(int x, int l, int r) {
    tree[x].m = 1;  // 乘法，初始化为1
    tree[x].a = 0;

    if (l == r) {
        tree[x].v = a[l];
    } else {
        int mid = (l + r) / 2;
        create(x * 2, l, mid);
        create(x * 2 + 1, mid + 1, r);
        update(x);
    }
    tree[x].v %= MOD;
}

void pushdown(int x, int l, int r) {
    int mid = (l + r) / 2;
    tree[x * 2].v =
        (tree[x * 2].v * tree[x].m + tree[x].a * (mid - l + 1)) % MOD;
    tree[x * 2 + 1].v =
        (tree[x * 2 + 1].v * tree[x].m + tree[x].a * (r - mid)) % MOD;
    // 子节点的值 * 乘法懒惰标记 + 加法懒惰标记 * 区间长度

    tree[x * 2].m = (tree[x].m * tree[x * 2].m) % MOD;
    tree[x * 2 + 1].m = (tree[x].m * tree[x * 2 + 1].m) % MOD;
    tree[x * 2].a = (tree[x * 2].a * tree[x].m + tree[x].a) % MOD;
    tree[x * 2 + 1].a = (tree[x * 2 + 1].a * tree[x].m + tree[x].a) % MOD;

    tree[x].m = 1;
    tree[x].a = 0;  // 清除父节点懒惰标记
}

void multi(int x, int cl, int cr, int l, int r, long long v) {
    if (r < cl or cr < l) {
        return;
    }
    if (l <= cl and cr <= r) {
        tree[x].v = (tree[x].v * v) % MOD;
        tree[x].m = (tree[x].m * v) % MOD;
        tree[x].a = (tree[x].a * v) % MOD;
    } else {
        pushdown(x, cl, cr);
        int mid = (cl + cr) / 2;
        multi(x * 2, cl, mid, l, r, v);
        multi(x * 2 + 1, mid + 1, cr, l, r, v);
        update(x);
    }
}

void add(int x, int cl, int cr, int l, int r, long long v) {
    if (r < cl or cr < l) {
        return;
    }
    if (l <= cl and cr <= r) {
        tree[x].a = (tree[x].a + v) % MOD;
        tree[x].v = (tree[x].v + v * (cr - cl + 1)) % MOD;
    } else {
        pushdown(x, cl, cr);
        int mid = (cl + cr) / 2;
        add(x * 2, cl, mid, l, r, v);
        add(x * 2 + 1, mid + 1, cr, l, r, v);
        update(x);
    }
}

long long query(int x, int cl, int cr, int l, int r) {
    if (r < cl or cr < l) {
        return 0;
    }
    if (l <= cl and cr <= r) {
        return tree[x].v % MOD;
    } else {
        pushdown(x, cl, cr);
        int mid = (cl + cr) / 2;
        return (query(x * 2, cl, mid, l, r) +
                query(x * 2 + 1, mid + 1, cr, l, r)) %
               MOD;
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