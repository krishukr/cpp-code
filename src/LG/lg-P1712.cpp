#include <algorithm>
#include <cstdio>
#include <iostream>
#include <memory>

constexpr int MAX_N = 500050;
constexpr int INF = 0x3f3f3f3f;

class SegTree {
   protected:
    struct Node {
        int m;
        int t;
    } tree[MAX_N << 3];

    void seg_merge(const int& x);

    void pushdown(const int& x);

   public:
    SegTree() = default;
    ~SegTree() = default;

    void mod(int x, int l, int r, const int& ml, const int& mr, const int& mv);

    const int query() const { return tree[1].m; }
};

struct S {
    int l, r;
    int len;

    S() = default;
    S(const int& l, const int& r) {
        this->l = l;
        this->r = r;
        this->len = r - l + 1;
    }
    ~S() = default;
} a[MAX_N];

int b[MAX_N << 1];
int tot;

template <typename T = int>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read(), m = read();
    for (int i = 1; i <= n; i++) {
        int l = read(), r = read();
        a[i] = S(l, r);
        b[++tot] = l;
        b[++tot] = r;
    }

    std::sort(a + 1, a + n + 1,
              [](const S& x, const S& y) { return x.len < y.len; });
    std::sort(b + 1, b + tot + 1);
    tot = std::unique(b + 1, b + tot + 1) - b - 1;

    for (int i = 1; i <= n; i++) {
        a[i].l = std::lower_bound(b + 1, b + tot + 1, a[i].l) - b;
        a[i].r = std::lower_bound(b + 1, b + tot + 1, a[i].r) - b;
    }

    int cl = 1, ans = INF;
    auto segTree = std::make_unique<SegTree>();

    for (int i = 1; i <= n; i++) {
        segTree->mod(1, 1, tot, a[i].l, a[i].r, 1);
        while (segTree->query() >= m) {
            ans = std::min(ans, a[i].len - a[cl].len);
            segTree->mod(1, 1, tot, a[cl].l, a[cl].r, -1);
            cl++;
        }
    }

    std::cout << (ans == INF ? -1 : ans) << '\n';

    return 0;
}

#define lc x * 2
#define rc x * 2 + 1

void SegTree::seg_merge(const int& x) {
    tree[x].m = std::max(tree[lc].m, tree[rc].m);
}

void SegTree::pushdown(const int& x) {
    if (tree[x].t) {
        tree[lc].m += tree[x].t;
        tree[lc].t += tree[x].t;
        tree[rc].m += tree[x].t;
        tree[rc].t += tree[x].t;
        tree[x].t = 0;
    }
}

void SegTree::mod(int x, int l, int r, const int& ml, const int& mr,
                  const int& mv) {
    if (r < ml or mr < l) {
        return;
    }
    if (ml <= l and r <= mr) {
        tree[x].m += mv;
        tree[x].t += mv;
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(x);
    if (ml <= mid) {
        mod(lc, l, mid, ml, mr, mv);
    }
    if (mid < mr) {
        mod(rc, mid + 1, r, ml, mr, mv);
    }
    seg_merge(x);
}

#undef lc
#undef rc

template <typename T = int>
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