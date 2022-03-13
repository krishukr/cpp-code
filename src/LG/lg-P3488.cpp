#include <cstdio>
#include <iostream>

class SegTree {
   private:
    typedef long long ll;

    const static int MAX_N = 1000050;

   protected:
    struct Node {
        ll s;
        ll m;
        ll l;
        ll r;
    } tree[MAX_N];

    void update(int x) {
        tree[x].s = tree[x * 2].s + tree[x * 2 + 1].s;
        tree[x].m = std::max(
            tree[x * 2].m,
            std::max(tree[x * 2 + 1].m, tree[x * 2].r + tree[x * 2 + 1].l));
        tree[x].l = std::max(tree[x * 2].l, tree[x * 2].s + tree[x * 2 + 1].l);
        tree[x].r =
            std::max(tree[x * 2 + 1].r, tree[x * 2 + 1].s + tree[x * 2].r);
    }

   public:
    SegTree() = default;
    SegTree(const int& n, const int& K) { build(1, 1, n, K); }
    ~SegTree() = default;

    void build(int x, int l, int r, const int& K) {
        if (l == r) {
            tree[x] = {-K, -K, 0, 0};
            return;
        }
        int mid = (l + r) / 2;
        build(x * 2, l, mid, K);
        build(x * 2 + 1, mid + 1, r, K);
        update(x);
    }

    void mod(int x, int l, int r, int q, int w) {
        if (l == r) {
            tree[x].s += w;
            tree[x].m += w;
            tree[x].l = tree[x].r = std::max<ll>(tree[x].s, 0);
            return;
        }
        int mid = (l + r) / 2;
        if (q <= mid) {
            mod(x * 2, l, mid, q, w);
        } else {
            mod(x * 2 + 1, mid + 1, r, q, w);
        }
        update(x);
    }

    const Node& operator[](const int& i) const { return this->tree[i]; }
};

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>(), k = read<int>(), d = read<int>();
    auto* segTree = new SegTree(n, k);

    for (int i = 1; i <= m; i++) {
        int x = read<int>(), y = read<int>();
        segTree->mod(1, 1, n, x, y);
        std::cout << ((*segTree)[1].m <= 1ll * k * d ? "TAK" : "NIE") << '\n';
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