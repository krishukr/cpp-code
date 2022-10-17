#include <cstdio>
#include <iostream>
#include <memory>

constexpr int MAX_N = 100050;
constexpr int INF = 0x3f3f3f3f;

class SegTree {
   public:
    SegTree() = default;
    ~SegTree() = default;

    struct Ele {
        int l;
        int r;
        int a;

        Ele() { this->l = this->r = this->a = 0; }
        Ele(int v, int op);
        Ele(int l, int r, int a);

        Ele operator+(const Ele& x) const;
    } tree[MAX_N << 2];

    void mod(int x, int l, int r, const int& mk, const int& mv, const int& op);
};

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    read(n);
    auto segTree = std::make_unique<SegTree>();
    for (int i = 1; i <= n; i++) {
        int op, x;
        read(op, x);
        segTree->mod(1, 1, n, i, x, op);
    }

    int q;
    read(q);
    while (q--) {
        int op;
        read(op);
        if (op <= 3) {
            int x, y;
            read(x, y);
            segTree->mod(1, 1, n, x, y, op);
        } else {
            int x;
            read(x);
            std::cout << std::max(std::min(x, segTree->tree[1].r),
                                  segTree->tree[1].l) +
                             segTree->tree[1].a
                      << '\n';
        }
    }

    return 0;
}

SegTree::Ele::Ele(int v, int op) {
    if (op == 1) {
        this->l = -INF;
        this->r = INF;
        this->a = v;
    } else if (op == 2) {
        this->l = -INF;
        this->r = v;
        this->a = 0;
    } else {
        this->l = v;
        this->r = INF;
        this->a = 0;
    }
}

SegTree::Ele::Ele(int l, int r, int a) {
    this->l = l;
    this->r = r;
    this->a = a;
}

SegTree::Ele SegTree::Ele::operator+(const SegTree::Ele& x) const {
    return {std::max(std::min(this->l, x.r - this->a), x.l - this->a),
            std::max(std::min(this->r, x.r - this->a), x.l - this->a),
            this->a + x.a};
}

#define lc (x << 1)
#define rc ((x << 1) | 1)

void SegTree::mod(int x, int l, int r, const int& mk, const int& mv,
                  const int& op) {
    if (l == r) {
        tree[x] = {mv, op};
        return;
    }
    const auto mid = (l + r) >> 1;
    if (mk <= mid) {
        mod(lc, l, mid, mk, mv, op);
    } else {
        mod(rc, mid + 1, r, mk, mv, op);
    }
    tree[x] = tree[lc] + tree[rc];
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