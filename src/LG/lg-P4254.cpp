#include <cmath>
#include <cstdio>
#include <iostream>
#include <memory>

constexpr int MAX_N = 1000050;
constexpr int N = 1000000;

class SegTree {
   public:
    struct L {
        double k;
        double b;

        double operator()(const int& x) { return k * (x - 1) + b; }
    } tree[MAX_N << 2];

    SegTree() = default;
    ~SegTree() = default;

    void mod(int x, int l, int r, L mv);

    double query(int x, int l, int r, const int& qk);
};

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

template <>
char read();

template <>
double read();

int main() {
    std::ios::sync_with_stdio(false);

    auto segTree = std::make_unique<SegTree>();
    int T;
    read(T);
    while (T--) {
        char op;
        read(op);
        if (op == 'P') {
            double b, k;
            read(b, k);
            segTree->mod(1, 1, N, {k, b});
        } else if (op == 'Q') {
            int x;
            read(x);
            std::cout << (int)(segTree->query(1, 1, N, x)) / 100 << '\n';
        }
    }

    return 0;
}

#define lc (x << 1)
#define rc ((x << 1) | 1)

void SegTree::mod(int x, int l, int r, L mv) {
    const auto mid = (l + r) >> 1;
    if (tree[x](mid) <= mv(mid)) {
        std::swap(tree[x], mv);
    }
    if (l == r) {
        return;
    }
    if (tree[x](l) <= mv(l)) {
        mod(lc, l, mid, mv);
    } else if (tree[x](r) <= mv(r)) {
        mod(rc, mid + 1, r, mv);
    }
}

double SegTree::query(int x, int l, int r, const int& qk) {
    if (l == r) {
        return tree[x](qk);
    }
    const auto mid = (l + r) >> 1;
    if (qk <= mid) {
        return std::max(tree[x](qk), query(lc, l, mid, qk));
    } else {
        return std::max(tree[x](qk), query(rc, mid + 1, r, qk));
    }
}

#undef lc
#undef rc

template <typename T>
T read() {
    T x = 0, f = 1;
    char ch = getchar_unlocked();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar_unlocked();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getchar_unlocked();
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

template <>
char read() {
    char ch = getchar_unlocked();
    while (ch != 'Q' and ch != 'P') {
        ch = getchar_unlocked();
    }
    return ch;
}

template <>
double read() {
    long long x = 0, f = 1, k = 0, b = 0;
    bool g = false;
    char ch = getchar_unlocked();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar_unlocked();
    }
    while (isdigit(ch) or ch == '.') {
        if (ch == '.') {
            g = true;
        } else if (!g) {
            x = x * 10 + ch - 48;
        } else {
            b = b * 10 + ch - 48;
            k++;
        }
        ch = getchar_unlocked();
    }
    return f * (std::pow(0.1, k) * b + x);
}