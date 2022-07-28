#include <cstdio>
#include <iostream>
#include <memory>

class SegTree {
   private:
    constexpr static int MAX_N = 100050;

   protected:
    struct Node {
        int l;
        int r;
    } tree[MAX_N << 2];

   public:
    SegTree() = default;
    ~SegTree() = default;

    void modl(int x, int l, int r, const int& mk);

    void modr(int x, int l, int r, const int& mk);

    int queryl(int x, int l, int r, const int& ql, const int& qr);

    int queryr(int x, int l, int r, const int& ql, const int& qr);
};

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m;
    read(n, m);
    auto segTree = std::make_unique<SegTree>();
    while (m--) {
        int op, x, y;
        read(op, x, y);
        if (op == 1) {
            segTree->modl(1, 1, n, x);
            segTree->modr(1, 1, n, y);
        } else if (op == 2) {
            std::cout << segTree->queryl(1, 1, n, 1, y) -
                             segTree->queryr(1, 1, n, 1, x - 1)
                      << '\n';
        }
    }

    return 0;
}

#define lc (x << 1)
#define rc ((x << 1) + 1)

void SegTree::modl(int x, int l, int r, const int& mk) {
    if (l == r) {
        tree[x].l++;
        return;
    }
    const auto mid = (l + r) >> 1;
    if (mk <= mid) {
        modl(lc, l, mid, mk);
    } else {
        modl(rc, mid + 1, r, mk);
    }
    tree[x].l = tree[lc].l + tree[rc].l;
}

void SegTree::modr(int x, int l, int r, const int& mk) {
    if (l == r) {
        tree[x].r++;
        return;
    }
    const auto mid = (l + r) >> 1;
    if (mk <= mid) {
        modr(lc, l, mid, mk);
    } else {
        modr(rc, mid + 1, r, mk);
    }
    tree[x].r = tree[lc].r + tree[rc].r;
}

int SegTree::queryl(int x, int l, int r, const int& ql, const int& qr) {
    if (ql <= l and r <= qr) {
        return tree[x].l;
    }
    const auto mid = (l + r) >> 1;
    int res{};
    if (ql <= mid) {
        res += queryl(lc, l, mid, ql, qr);
    }
    if (mid < qr) {
        res += queryl(rc, mid + 1, r, ql, qr);
    }
    return res;
}

int SegTree::queryr(int x, int l, int r, const int& ql, const int& qr) {
    if (ql <= l and r <= qr) {
        return tree[x].r;
    }
    const auto mid = (l + r) >> 1;
    int res{};
    if (ql <= mid) {
        res += queryr(lc, l, mid, ql, qr);
    }
    if (mid < qr) {
        res += queryr(rc, mid + 1, r, ql, qr);
    }
    return res;
}

#undef lc
#undef rc

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