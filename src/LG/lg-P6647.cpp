#include <climits>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stack>

using ll = long long;

constexpr int MAX_N = 1000050;

class SegTree {
   protected:
    struct Node {
        ll t;
        ll m;
    } tree[MAX_N << 2];

    void seg_merge(const int& x);

    void pushdown(const int& x);

   public:
    SegTree() = default;
    ~SegTree() = default;

    void mod(int x, int l, int r, const int& ml, const int& mr, const ll& mv);

    ll query(int x, int l, int r, const int& ql, const int& qr);
};

ll a[MAX_N], f[MAX_N];
std::stack<int> stk;
std::unique_ptr<SegTree> segTree = nullptr;
int n, k;

void calc(int x);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    segTree = std::make_unique<SegTree>();
    read(n, k);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }

    stk.push(0);
    a[0] = (LLONG_MAX >> 2);

    for (int i = 1; i <= n; i++) {
        calc(i);
        int l = std::max(i - k, 0), r = (i - 1) - ((i - 1) % k);
        f[i] = segTree->query(1, 0, n, l, r);
        segTree->mod(1, 0, n, i, i, f[i]);
    }
    std::cout << f[n] << '\n';

    return 0;
}

#define lc x * 2
#define rc x * 2 + 1

void SegTree::seg_merge(const int& x) {
    tree[x].m = std::max(tree[lc].m, tree[rc].m);
}

void SegTree::pushdown(const int& x) {
    tree[lc].t += tree[x].t;
    tree[lc].m += tree[x].t;
    tree[rc].t += tree[x].t;
    tree[rc].m += tree[x].t;
    tree[x].t = 0;
}

void SegTree::mod(int x, int l, int r, const int& ml, const int& mr,
                  const ll& mv) {
    if (ml <= l and r <= mr) {
        tree[x].m += mv;
        tree[x].t += mv;
        return;
    }
    const int mid = (l + r) >> 1;
    pushdown(x);
    if (ml <= mid) {
        mod(lc, l, mid, ml, mr, mv);
    }
    if (mid < mr) {
        mod(rc, mid + 1, r, ml, mr, mv);
    }
    seg_merge(x);
}

ll SegTree::query(int x, int l, int r, const int& ql, const int& qr) {
    if (ql <= l and r <= qr) {
        return tree[x].m;
    }
    const int mid = (l + r) >> 1;
    pushdown(x);
    ll res{};
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

void calc(int x) {
    segTree->mod(1, 0, n, x - 1, x - 1, a[x]);
    int l = x - 2;
    while (a[stk.top()] < a[x]) {
        auto p = a[stk.top()];
        stk.pop();
        segTree->mod(1, 0, n, stk.top(), l, a[x] - p);
        l = stk.top() - 1;
    }
    stk.push(x);
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