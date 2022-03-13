#include <cstdio>
#include <iostream>

class SegTree {
   private:
    typedef long long ll;
    constexpr static int MAX_N = 2000050;
    constexpr static int INF = 0x3f3f3f3f;
    int* A;

   protected:
#define lc x * 2
#define rc x * 2 + 1

    struct Node {
        int l;    // 左端点
        int r;    // 右端点
        ll s;     // 区间和
        int m;    // 最大值
        int tm;   // 最大值标记
        int n;    // 次大值
        int tn;   // 次大值标记
        int hm;   // 历史最大值
        int thm;  // 历史最大值标记
        int hn;   // 历史次大值
        int thn;  // 历史次大值标记
        int mc;   // 最大值出现次数
    } tree[MAX_N];

    /**
     * @brief 合并区间
     *
     * @param x 当前索引
     *
     * @details 更新 [区间和, 最大值, 历史最大值]
     */
    void seg_merge(int x) {
        tree[x].s = tree[lc].s + tree[rc].s;
        tree[x].m = std::max(tree[lc].m, tree[rc].m);
        tree[x].hm = std::max(tree[lc].hm, tree[rc].hm);

        if (tree[lc].m == tree[rc].m) {  // 最大值相同
            tree[x].n = std::max(tree[lc].n, tree[rc].n);
            tree[x].mc = tree[lc].mc + tree[rc].mc;
        } else if (tree[lc].m > tree[rc].m) {  // 最大值在左
            tree[x].n = std::max(tree[lc].n, tree[rc].m);
            tree[x].mc = tree[lc].mc;
        } else {  //最大值在右
            tree[x].n = std::max(tree[lc].m, tree[rc].n);
            tree[x].mc = tree[rc].mc;
        }
    }

    /**
     * @brief 更新标记
     *
     * @param x 当前索引
     * @param am 最大值增量
     * @param ahm 历史最大值增量
     * @param anm 非最大值增量
     * @param anhm 非最大的历史最大值增量
     */
    void update(int x, int am, int ahm, int anm, int anhm) {
        tree[x].s += 1ll * am * tree[x].mc +
                     1ll * anm * (tree[x].r - tree[x].l + 1 - tree[x].mc);
        tree[x].hm = std::max(tree[x].hm, tree[x].m + ahm);
        tree[x].thm = std::max(tree[x].thm, tree[x].tm + ahm);
        tree[x].thn = std::max(tree[x].thn, tree[x].tn + anhm);
        // 最大的历史最大值改变，更新标记
        tree[x].m += am;
        tree[x].tm += am;
        tree[x].n += anm;
        tree[x].tn += anm;

        if (tree[x].n != -INF) {  // 区间有次大值
            tree[x].hn += anm;
        }
    }

    /**
     * @brief 下传标记
     *
     * @param x 当前索引
     */
    void pushdown(int x) {
        int cm = std::max(tree[lc].m, tree[rc].m);  // 区间最大值

        if (tree[lc].m == cm) {  // 左有最大值
            // 向左传递最大值
            update(lc, tree[x].tm, tree[x].thm, tree[x].tn, tree[x].thn);
        } else {
            // 向左传递次大值
            update(lc, tree[x].tn, tree[x].thn, tree[x].tn, tree[x].thn);
        }
        if (tree[rc].m == cm) {  // 右有最大值
            // 向右传递最大值
            update(rc, tree[x].tm, tree[x].thm, tree[x].tn, tree[x].thn);
        } else {
            // 向右传递次大值
            update(rc, tree[x].tn, tree[x].thn, tree[x].tn, tree[x].thn);
        }
        // 已下传，清除标记
        tree[x].tm = tree[x].tn = tree[x].thm = tree[x].thn = 0;
    }

    /**
     * @brief 建树
     *
     * @param x 当前索引
     * @param l 区间左端点
     * @param r 区间右端点
     */
    void build(int x, int l, int r) {
        tree[x].l = l;
        tree[x].r = r;
        if (l == r) {
            tree[x].s = tree[x].m = tree[x].hm = A[l];
            tree[x].mc = 1;  // 就自己
            tree[x].n = -INF;
            return;
        }

        int mid = (l + r) / 2;
        build(lc, l, mid);
        build(rc, mid + 1, r);
        seg_merge(x);
    }

   public:
    SegTree(int n, int* A) {
        this->A = A;
        build(1, 1, n);
    }
    ~SegTree() = default;

    /**
     * @brief 区间加法
     *
     * @param x 当前索引
     * @param ml 修改区间左端点
     * @param mr 修改区间右端点
     * @param mv 修改增量
     */
    void mod_add(int x, const int& ml, const int& mr, const int& mv) {
        if (tree[x].l > mr or tree[x].r < ml) {  // 不在区间内
            return;
        }
        if (ml <= tree[x].l and tree[x].r <= mr) {  // 区间完全覆盖
            update(x, mv, mv, mv, mv);
            return;
        }

        pushdown(x);
        mod_add(lc, ml, mr, mv);
        mod_add(rc, ml, mr, mv);
        seg_merge(x);
    }

    /**
     * @brief 区间每个取 min
     *
     * @param x 当前索引
     * @param ml 修改区间左端点
     * @param mr 修改区间右端点
     * @param mv 对其取 min
     */
    void mod_min(int x, const int& ml, const int& mr, const int& mv) {
        if (tree[x].l > mr or tree[x].r < ml) {  // 不在区间内
            return;
        }
        if (tree[x].m <= mv) {  // 最大值都比 mv 小
            return;
        }
        if (ml <= tree[x].l and tree[x].r <= mr) {  // 区间完全覆盖
            if (tree[x].n < mv) {                   // 有修改
                update(x, mv - tree[x].m, mv - tree[x].m, 0, 0);
                return;
            }
        }

        pushdown(x);
        mod_min(lc, ml, mr, mv);
        mod_min(rc, ml, mr, mv);
        seg_merge(x);
    }

    /**
     * @brief 查询区间和
     *
     * @param x 当前索引
     * @param ql 查询区间左端点
     * @param qr 查询区间右端点
     * @return long long 区间和
     */
    ll query_sum(int x, const int& ql, const int& qr) {
        if (tree[x].l > qr or tree[x].r < ql) {  // 不在区间内
            return 0;
        }
        if (ql <= tree[x].l and tree[x].r <= qr) {  // 区间完全覆盖
            return tree[x].s;
        }

        pushdown(x);
        return query_sum(lc, ql, qr) + query_sum(rc, ql, qr);
    }

    /**
     * @brief 查询区间最大值
     *
     * @param x 当前索引
     * @param ql 查询区间左端点
     * @param qr 查询区间右端点
     * @return int 区间最大值
     */
    int query_max(int x, const int& ql, const int& qr) {
        if (tree[x].l > qr or tree[x].r < ql) {  // 不在区间内
            return -INF;
        }
        if (ql <= tree[x].l and tree[x].r <= qr) {  // 区间完全覆盖
            return tree[x].m;
        }

        pushdown(x);
        return std::max(query_max(lc, ql, qr), query_max(rc, ql, qr));
    }

    /**
     * @brief 查询区间历史最大值
     *
     * @param x 当前索引
     * @param ql 查询区间左端点
     * @param qr 查询区间右端点
     * @return int 区间历史最大值
     */
    int query_history_max(int x, const int& ql, const int& qr) {
        if (tree[x].l > qr or tree[x].r < ql) {  // 不在区间内
            return -INF;
        }
        if (ql <= tree[x].l and tree[x].r <= qr) {  // 区间完全覆盖
            return tree[x].hm;
        }

        pushdown(x);
        return std::max(query_history_max(lc, ql, qr),
                        query_history_max(rc, ql, qr));
    }
};

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), m = read<int>();
    auto* A = new int[n + 10];
    for (int i = 1; i <= n; i++) {
        A[i] = read<int>();
    }

    auto* segTree = new SegTree(n, A);
    for (int i = 1; i <= m; i++) {
        int op = read<int>(), l = read<int>(), r = read<int>(), v;
        switch (op) {
            case 1:
                v = read<int>();
                segTree->mod_add(1, l, r, v);
                break;
            case 2:
                v = read<int>();
                segTree->mod_min(1, l, r, v);
                break;
            case 3:
                std::cout << segTree->query_sum(1, l, r) << '\n';
                break;
            case 4:
                std::cout << segTree->query_max(1, l, r) << '\n';
                break;
            case 5:
                std::cout << segTree->query_history_max(1, l, r) << '\n';
                break;
            default:
                throw std::runtime_error("Test data is wrong.");
        }
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