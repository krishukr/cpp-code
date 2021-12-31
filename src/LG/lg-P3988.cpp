#include <cstdio>
#include <iostream>

template <typename T>
T read();

class SegTree {
   private:
    const static int MAX_N = 1000050;

   protected:
    int tree[MAX_N << 2];

    void update(int x);

    void build(int x, int l, int r);

   public:
    SegTree() = delete;
    SegTree(int n) { build(1, 1, n); }
    ~SegTree() = default;

    int query(int x, int l, int r, int k);
};

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    auto* segTree = new SegTree(n);

    int lst = 0;
    for (int i = n; i > 0; i--) {
        int x = read<int>();
        lst += x;
        lst %= i;
        std::cout << segTree->query(1, 1, n, lst + 1) << '\n';
    }

    return 0;
}

void SegTree::update(int x) { tree[x] = tree[x * 2] + tree[x * 2 + 1]; }

void SegTree::build(int x, int l, int r) {
    if (l == r) {
        tree[x] = 1;
        return;
    }
    int mid = (l + r) / 2;
    build(x * 2, l, mid);
    build(x * 2 + 1, mid + 1, r);
    update(x);
}

int SegTree::query(int x, int l, int r, int k) {
    tree[x]--;
    if (l == r) {
        return l;
    }

    int mid = (l + r) / 2;
    if (k <= tree[x * 2]) {
        return query(x * 2, l, mid, k);
    } else {
        return query(x * 2 + 1, mid + 1, r, k - tree[x * 2]);
    }
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