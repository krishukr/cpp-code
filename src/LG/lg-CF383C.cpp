#include <cstdio>
#include <iostream>

int n;

template <typename T>
T read();

class Star {
   private:
    const static int MAX_N = 200050;

   protected:
    struct Node {
        int v;
        int nxt;
    } node[MAX_N << 1];

    int head[MAX_N << 1];
    int cnt;

   public:
    void create(int u, int v) {
        node[++cnt].v = v;
        node[cnt].nxt = head[u];
        head[u] = cnt;
    }
};

class SegTree {
   private:
    const static int MAX_N = 200050;

   protected:
    int tree[MAX_N << 2];

   public:
    void mod(int x, int l, int r, int ql, int qr, int w) {
        if (ql <= l and r <= qr) {
            tree[x] += w;
            return;
        }
        int mid = (l + r) / 2;
        if (ql <= mid) {
            mod(x * 2, l, mid, ql, qr, w);
        }
        if (mid < qr) {
            mod(x * 2 + 1, mid + 1, r, ql, qr, w);
        }
    }

    int query(int x, int l, int r, int k, int o) {
        if (l == r) {
            return tree[x] * o;
        }
        int mid = (l + r) / 2;
        if (k <= mid) {
            return tree[x] * o + query(x * 2, l, mid, k, o);
        } else {
            return tree[x] * o + query(x * 2 + 1, mid + 1, r, k, o);
        }
    }
};

class Soulution : public Star, public SegTree {
   private:
    const static int MAX_N = 200050;

   protected:
    int n;
    int w[MAX_N];

    int dfn[MAX_N], siz[MAX_N], dep[MAX_N];
    int idx;

    void dfs(int x, int f) {
        dep[x] = dep[f] + 1;
        dfn[x] = ++idx;
        siz[x] = 1;

        for (int i = head[x]; i; i = node[i].nxt) {
            int v = node[i].v;
            if (v == f) {
                continue;
            }
            dfs(v, x);
            siz[x] += siz[v];
        }
    }

   public:
    void solve() {
        n = read<int>();
        int m = read<int>();

        for (int i = 1; i <= n; i++) {
            w[i] = read<int>();
        }
        for (int i = 1; i < n; i++) {
            int x = read<int>(), y = read<int>();
            create(x, y);
            create(y, x);
        }
        dfs(1, 0);

        for (int i = 1; i <= m; i++) {
            int op = read<int>();
            if (op == 1) {
                int x = read<int>(), y = read<int>();
                if ((dep[x] & 1) == 0) {
                    y = -y;
                }
                mod(1, 1, n, dfn[x], dfn[x] + siz[x] - 1, y);
            } else {
                int x = read<int>();
                if ((dep[x] & 1) == 0) {
                    std::cout << w[x] + query(1, 1, n, dfn[x], -1) << '\n';
                } else {
                    std::cout << w[x] + query(1, 1, n, dfn[x], 1) << '\n';
                }
            }
        }
    }
};

int main() {
    std::ios::sync_with_stdio(false);

    Soulution* solution = new Soulution();
    solution->solve();
    delete solution;

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