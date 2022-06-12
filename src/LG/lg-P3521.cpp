#include <cstdio>
#include <iostream>
#include <memory>

using ll = long long;

constexpr int MAX_N = 200050;

class SegTree {
   private:
    struct Node {
        int l;
        int r;
        int a;
    } tree[MAX_N << 5];

    int cnt;

    int n;
    ll ab, af;
    ll ans;

    void mod(int& x, int l, int r, const int& mk);

    int tree_merge(int a, int b, int l, int r);

    void new_case() { ab = af = 0; }

    int dfs();

   public:
    SegTree(const int n);
    ~SegTree() = default;

    ll query() const { return ans; }
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
    auto segTree = std::make_unique<SegTree>(n);
    std::cout << segTree->query() << '\n';

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

    const int mid = (l + r) >> 1;
    if (mk <= mid) {
        mod(lc, l, mid, mk);
    } else {
        mod(rc, mid + 1, r, mk);
    }
}

int SegTree::tree_merge(int a, int b, int l, int r) {
    if (!a or !b) {
        return a + b;
    }
    if (l == r) {
        tree[a].a += tree[b].a;
        return a;
    }
    ab += 1ll * tree[tree[a].r].a * tree[tree[b].l].a;
    af += 1ll * tree[tree[b].r].a * tree[tree[a].l].a;

    const int mid = (l + r) >> 1;
    tree[a].l = tree_merge(tree[a].l, tree[b].l, l, mid);
    tree[a].r = tree_merge(tree[a].r, tree[b].r, mid + 1, r);
    tree[a].a += tree[b].a;
    return a;
}

int SegTree::dfs() {
    int x{}, v;
    read(v);
    if (v == 0) {
        int l = dfs(), r = dfs();
        new_case();
        x = tree_merge(l, r, 1, n);
        ans += std::min(ab, af);
    } else {
        mod(x, 1, n, v);
    }
    return x;
}

SegTree::SegTree(const int n) {
    this->n = n;
    dfs();
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