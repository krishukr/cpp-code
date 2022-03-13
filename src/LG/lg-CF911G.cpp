#include <cstdio>
#include <iostream>

class SegTree {
   private:
    constexpr static int MAX_N = 10000050;

   protected:
    struct Node {
        int l;
        int r;
    } tree[MAX_N];

    int cnt;

    /**
     * @brief 合并点
     *
     * @return int 合并后索引
     */
    int merge(int a, int b) {
        if (!a or !b) {    // 有未开的树
            return a | b;  // 直接返回已经开过的
        }

        tree[a].l = merge(tree[a].l, tree[b].l);
        tree[a].r = merge(tree[a].r, tree[b].r);
        return a;
    }

   public:
    SegTree() = default;
    ~SegTree() = default;

    int ans[MAX_N];

    /**
     * @brief 生成点
     *
     * @param x 当前父节点
     * @param l 当前左端点
     * @param r 当前右端点
     * @param p 创建位置
     */
    void build(int& x, int l, int r, const int& p) {
        if (l > p or p > r) {
            return;
        }
        if (!x) {
            x = ++cnt;  // 创建新点
        }
        if (l == r) {
            return;
        }

        int mid = (l + r) / 2;
        build(tree[x].l, l, mid, p);
        build(tree[x].r, mid + 1, r, p);
    }

    /**
     * @brief 区间替换
     *
     * @param a 替换前元素
     * @param b 替换后元素
     * @param l 当前左端点
     * @param r 当前右端点
     * @param ml 修改区间左端点
     * @param mr 修改区间右端点
     */
    void replace(int& a, int& b, int l, int r, const int& ml, const int& mr) {
        if (a == b) {
            return;
        }
        if (!a) {  // 不存在替换前元素
            return;
        }
        if (l > mr or ml > r) {
            return;
        }

        if (ml <= l and r <= mr) {
            b = merge(a, b);
            a = 0;
            return;
        }
        if (!b) {
            b = ++cnt;
        }

        int mid = (l + r) / 2;
        replace(tree[a].l, tree[b].l, l, mid, ml, mr);
        replace(tree[a].r, tree[b].r, mid + 1, r, ml, mr);
    }

    /**
     * @brief 求解答案
     *
     * @param x 当前索引
     * @param l 当前左端点
     * @param r 当前右端点
     * @param t 当前求值，即查询树
     */
    void solve(int x, int l, int r, const int& t) {
        if (!x) {  // 未创建的点
            return;
        }
        if (l == r) {
            ans[l] = t;
            return;
        }

        int mid = (l + r) / 2;
        solve(tree[x].l, l, mid, t);
        solve(tree[x].r, mid + 1, r, t);
    }
};

int root[105];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    auto* segTree = new SegTree();
    for (int i = 1; i <= n; i++) {
        int x = read<int>();
        segTree->build(root[x], 1, n, i);
    }

    int q = read<int>();
    while (q--) {
        int l = read<int>(), r = read<int>(), x = read<int>(), y = read<int>();
        segTree->replace(root[x], root[y], 1, n, l, r);
    }

    for (int i = 1; i <= 100; i++) {
        segTree->solve(root[i], 1, n, i);
    }

    for (int i = 1; i <= n; i++) {
        std::cout << segTree->ans[i] << ' ';
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