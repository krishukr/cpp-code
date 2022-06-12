#include <cstdio>
#include <iostream>
#include <memory>
#include <vector>

using ll = long long;

constexpr int MAX_N = 300050;

class SegTree {
   private:
    struct Node {
        int l;
        int r;
        int a;
    } tree[MAX_N << 4];

    int root[MAX_N];
    int cnt;

    void mod(int& x, int l, int r, const int& mk);

    int query(int x, int l, int r, const int& qk);

    int n, m, mx;

   public:
    SegTree() = default;
    SegTree(const int n, const int m, const int& q) {
        this->n = n;
        this->m = m;
        this->mx = std::max(n, m) + q;
    }
    ~SegTree() = default;

    std::vector<ll> V[MAX_N];

    ll del_column(const int& x);

    ll del_row(const int& x, const int& y);
};

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    freopen("phalanx.in", "r", stdin);
    freopen("phalanx.out", "w", stdout);
    std::ios::sync_with_stdio(false);

    int n, m, q;
    read(n, m, q);
    auto segTree = std::make_unique<SegTree>(n, m, q);
    while (q--) {
        int x, y;
        read(x, y);
        if (y == m) {
            const auto p = segTree->del_column(x);
            std::cout << p << '\n';
            segTree->V[n + 1].push_back(p);
        } else {
            {
                const auto p = segTree->del_row(x, y);
                std::cout << p << '\n';
                segTree->V[n + 1].push_back(p);
            }
            {
                const auto p = segTree->del_column(x);
                segTree->V[x].push_back(p);
            }
        }
    }

    std::cout << std::flush;
    fclose(stdin);
    fclose(stdout);
    return 0;
}

#define lc tree[x].l
#define rc tree[x].r

void SegTree::mod(int& x, int l, int r, const int& mk) {
    if (!x) {
        x = ++cnt;
    }
    tree[x].a++;
    if (l == r) {
        return;
    }
    const int mid = (l + r) / 2;
    if (mk <= mid) {
        mod(lc, l, mid, mk);
    } else {
        mod(rc, mid + 1, r, mk);
    }
}

int SegTree::query(int x, int l, int r, const int& qk) {
    if (l == r) {
        return l;
    }
    const int mid = (l + r) / 2;
    const int lk = mid - l + 1 - tree[lc].a;
    if (qk <= lk) {
        return query(lc, l, mid, qk);
    } else {
        return query(rc, mid + 1, r, qk - lk);
    }
}

#undef lc
#undef rc

ll SegTree::del_column(const int& x) {
    const int p = query(root[n + 1], 1, mx, x);
    mod(root[n + 1], 1, mx, p);
    return ((p <= n) ? ((ll)(p - 1) * m + m) : V[n + 1][p - n - 1]);
}

ll SegTree::del_row(const int& x, const int& y) {
    const int p = query(root[x], 1, mx, y);
    mod(root[x], 1, mx, p);
    return ((p < m) ? ((ll)(x - 1) * m + p) : V[x][p - m]);
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

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}