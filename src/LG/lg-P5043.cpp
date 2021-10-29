#include <algorithm>
#include <cstdio>
#include <functional>
#include <iostream>

template <typename T>
T read();

class Tree {
   private:
    typedef unsigned long long ll;

    const static int MAX_N = 150;
    const static ll SEED = 131;
    const static ll DELTA = 114514;

   protected:
    struct Node {
        int v;
        int nxt;
    } node[MAX_N];

    int head[MAX_N];
    int cnt;

   public:
    Tree() = default;
    ~Tree() = default;

    ll hsh[MAX_N];

    void create(int u, int v) {
        node[++cnt].v = v;
        node[cnt].nxt = head[u];
        head[u] = cnt;
    }

    void gethash(int n) {
        std::function<ll(int, int)> dfs;
        dfs = [&](int x, int f) -> ll {
            ll stk[MAX_N];
            ll res = 0, top = 0;

            for (int i = head[x]; i; i = node[i].nxt) {
                int v = node[i].v;
                if (v == f) {
                    continue;
                }
                stk[++top] = dfs(v, x);
            }
            std::sort(stk + 1, stk + top + 1);
            for (int i = 1; i <= top; i++) {
                res = res * SEED + stk[i] + DELTA;
            }
            return res * SEED + DELTA;
        };

        for (int i = 1; i <= n; i++) {
            hsh[i] = dfs(i, 0);
        }
        std::sort(hsh + 1, hsh + n + 1);
    }
};

int main() {
    std::ios::sync_with_stdio(false);

    int m = read<int>();
    auto **trees = new Tree *[m + 1] {};
    for (int i = 0; i <= m; i++) {
        trees[i] = new Tree();
    }

    for (int kkk = 1; kkk <= m; kkk++) {
        auto *tree = trees[kkk];
        int n = read<int>();
        for (int i = 1; i <= n; i++) {
            int x = read<int>();
            if (x) {
                tree->create(i, x);
                tree->create(x, i);
            }
        }

        tree->gethash(n);

        for (int i = 1, j = 0; i <= kkk; i++) {
            while (j <= n) {
                j++;
                if (tree->hsh[j] != trees[i]->hsh[j]) {
                    break;
                }
            }
            if (j > n) {
                std::cout << i << '\n';
                break;
            }
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