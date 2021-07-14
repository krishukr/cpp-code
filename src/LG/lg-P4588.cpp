#include <cstdio>
#include <iostream>

const int MAX_N = 1000050;
int MOD;

long long tree[MAX_N * 2];

void update(int x);

void create(int x, int l, int r);

void mod(int x, int l, int r, int k, int v);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int T = read<int>();
    while (T--) {
        int q = read<int>();
        MOD = read<int>();
        create(1, 1, q);
        for (int i = 1; i <= q; i++) {
            int op = read<int>(), x = read<int>();
            if (op == 1) {
                mod(1, 1, q, i, x);
                std::cout << tree[1] % MOD << '\n';
            } else {
                mod(1, 1, q, x, 0);
                std::cout << tree[1] % MOD << '\n';
            }
        }
    }

    return 0;
}

void update(int x) { tree[x] = (tree[x * 2] * tree[x * 2 + 1]) % MOD; }

void create(int x, int l, int r) {
    tree[x] = 1;
    if (l == r) {
        return;
    } else {
        int mid = (l + r) / 2;
        create(x * 2, l, mid);
        create(x * 2 + 1, mid + 1, r);
    }
}

void mod(int x, int l, int r, int k, int v) {
    if (l == r) {
        tree[x] = (v ? v : 1);
    } else {
        int mid = (l + r) / 2;
        if (k <= mid) {
            mod(x * 2, l, mid, k, v);
        } else {
            mod(x * 2 + 1, mid + 1, r, k, v);
        }
        update(x);
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