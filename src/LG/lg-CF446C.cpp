#include <cstdio>
#include <iostream>

typedef long long ll;

constexpr int MOD = 1e9 + 9;

ll fib[300050];

template <typename T>
T read();

class SegTree {
   private:
    constexpr static int MAX_N = 1200050;
    int* A;

   protected:
#define lc x * 2
#define rc x * 2 + 1

    struct Node {
        int l;
        int r;
        ll s;
        ll t1;
        ll t2;
    } tree[MAX_N];

    void seg_merge(int x) {
        tree[x].s = tree[lc].s + tree[rc].s;
        tree[x].s %= MOD;
    }

    void pushdown(int x) {
        if (tree[x].t1 or tree[x].t2) {
            const int &l = tree[x].l, &r = tree[x].r;
            int p = (l + r) / 2 - l + 2;
            tree[lc].t1 += tree[x].t1;
            tree[lc].t1 %= MOD;
            tree[lc].t2 += tree[x].t2;
            tree[lc].t2 %= MOD;
            tree[lc].s +=
                tree[x].t2 * (fib[p] - 1) % MOD + tree[x].t1 * fib[p - 1] % MOD;
            tree[lc].s %= MOD;

            tree[rc].t1 +=
                tree[x].t2 * fib[p - 1] % MOD + tree[x].t1 * fib[p - 2] % MOD;
            tree[rc].t1 %= MOD;
            tree[rc].t2 +=
                tree[x].t2 * fib[p] % MOD + tree[x].t1 * fib[p - 1] % MOD;
            tree[rc].t2 %= MOD;
            tree[rc].s += tree[x].t2 * (fib[r - l + 2] - 1) % MOD +
                          tree[x].t1 * fib[r - l + 1] % MOD -
                          tree[x].t2 * (fib[p] - 1) % MOD -
                          tree[x].t1 * fib[p - 1] % MOD;
            tree[rc].s %= MOD;

            tree[x].t1 = tree[x].t2 = 0;
        }
    }

    void build(int x, int l, int r) {
        tree[x].l = l;
        tree[x].r = r;
        if (l == r) {
            tree[x].s = A[l];
            return;
        }

        int mid = (l + r) / 2;
        build(lc, l, mid);
        build(rc, mid + 1, r);
        seg_merge(x);
    }

   public:
    SegTree(int n, int* A) {
        this->A = A;
        build(1, 1, n);
    }
    ~SegTree() = default;

    void mod_add_fib(int x, int ml, int mr) {
        if (tree[x].l > mr or ml > tree[x].r) {
            return;
        }
        if (ml <= tree[x].l and tree[x].r <= mr) {
            const int &l = tree[x].l, &r = tree[x].r;
            tree[x].t1 += fib[l - ml + 1];
            tree[x].t1 %= MOD;
            tree[x].t2 += fib[l - ml + 2];
            tree[x].t2 %= MOD;
            tree[x].s += fib[r - l + 1] * fib[l - ml + 1] % MOD +
                         (fib[r - l + 2] - 1) * fib[l - ml + 2] % MOD;
            tree[x].s %= MOD;
            return;
        }

        pushdown(x);
        mod_add_fib(lc, ml, mr);
        mod_add_fib(rc, ml, mr);
        seg_merge(x);
    }

    ll query(int x, int ql, int qr) {
        if (tree[x].l > qr or ql > tree[x].r) {
            return 0;
        }
        if (ql <= tree[x].l and tree[x].r <= qr) {
            return tree[x].s;
        }

        pushdown(x);
        return (query(lc, ql, qr) + query(rc, ql, qr)) % MOD;
    }
};

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>();
    fib[1] = fib[2] = 1;
    for (int i = 3; i <= n + 5; i++) {
        fib[i] = fib[i - 1] + fib[i - 2];
        fib[i] %= MOD;
    }

    auto* A = new int[n + 10];
    for (int i = 1; i <= n; i++) {
        A[i] = read<int>();
    }
    auto* segTree = new SegTree(n, A);

    for (int i = 1; i <= m; i++) {
        int op = read<int>(), l = read<int>(), r = read<int>();
        if (op == 1) {
            segTree->mod_add_fib(1, l, r);
        } else {
            std::cout << (segTree->query(1, l, r) % MOD + MOD) % MOD << '\n';
        }
    }

    return 0;
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