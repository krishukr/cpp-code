#include <cstdio>
#include <iostream>
#include <memory>
#include <set>

constexpr int MAX_N = 500050;

int a[MAX_N], b[MAX_N];
std::set<int> s[MAX_N];

int tree[MAX_N << 2];

void seg_merge(const int& x);

void build(int x, int l, int r);

void mod(int x, int l, int r, const int& mk, const int& mv);

int query(int x, int l, int r, const int& ql, const int& qr);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m, w;
    read(n, m, w);
    for (int i = 0; i <= w; i++) {
        s[i].insert(0);
        s[i].insert(n + 1);
    }
    for (int i = 1; i <= n; i++) {
        read(a[i]);
        auto it1 = s[w - a[i]].lower_bound(i);
        it1--;
        auto it2 = s[a[i]].upper_bound(i);
        it2--;
        b[i] = *it1 < *it2 ? 0 : *it1;

        s[a[i]].insert(i);
    }
    build(1, 1, n);

    int lac{};
    while (m--) {
        int op, x, y;
        read(op, x, y);
        if (op == 1) {
            if (a[x] == y) {
                continue;
            }
            s[a[x]].erase(s[a[x]].find(x));
            auto it1 = s[w - a[x]].lower_bound(x);
            auto pt1 = it1;
            pt1--;
            auto it2 = s[a[x]].lower_bound(x);
            auto pt2 = it2;
            pt2--;

            if (b[*it1] == x) {
                b[*it1] = *pt1 < *pt2 ? *pt2 : 0;
                mod(1, 1, n, *it1, b[*it1]);
            }
            if (*it2 < *it1 and b[x] != 0 and b[x] != n + 1) {
                b[*it2] = *pt1;
                mod(1, 1, n, *it2, b[*it2]);
            }

            it1 = s[w - y].upper_bound(x);
            pt1 = it1;
            pt1--;
            it2 = s[y].upper_bound(x);
            pt2 = it2;
            pt2--;
            b[x] = *pt1 > *pt2 ? *pt1 : 0;
            mod(1, 1, n, x, b[x]);

            if (*it1 < *it2) {
                b[*it1] = x;
                mod(1, 1, n, *it1, b[*it1]);
            } else {
                b[*it2] = 0;
                mod(1, 1, n, *it2, b[*it2]);
            }

            s[y].insert(x);
            a[x] = y;
        } else if (op == 2) {
            x ^= lac;
            y ^= lac;
            if (x <= query(1, 1, n, x, y)) {
                lac++;
                std::cout << "Yes\n";
            } else {
                std::cout << "No\n";
            }
        }
    }

    return 0;
}

#define lc (x << 1)
#define rc ((x << 1) + 1)

void seg_merge(const int& x) { tree[x] = std::max(tree[lc], tree[rc]); }

void build(int x, int l, int r) {
    if (l == r) {
        tree[x] = b[l];
        return;
    }
    const auto mid = (l + r) >> 1;
    build(lc, l, mid);
    build(rc, mid + 1, r);
    seg_merge(x);
}

void mod(int x, int l, int r, const int& mk, const int& mv) {
    if (l == r) {
        tree[x] = mv;
        return;
    }
    const auto mid = (l + r) >> 1;
    if (mk <= mid) {
        mod(lc, l, mid, mk, mv);
    }
    if (mid < mk) {
        mod(rc, mid + 1, r, mk, mv);
    }
    seg_merge(x);
}

int query(int x, int l, int r, const int& ql, const int& qr) {
    if (ql <= l and r <= qr) {
        return tree[x];
    }
    const auto mid = (l + r) >> 1;
    int res{-0x3f3f3f3f};
    if (ql <= mid) {
        res = std::max(res, query(lc, l, mid, ql, qr));
    }
    if (mid < qr) {
        res = std::max(res, query(rc, mid + 1, r, ql, qr));
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
