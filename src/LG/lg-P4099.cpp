#include <cstdio>
#include <cstring>
#include <iostream>
#include <memory>

typedef long long ll;

constexpr int MOD = 1e9 + 7;
constexpr int MAX_N = 1050;

ll C[MAX_N][MAX_N];

class Solution {
   private:
    struct Node {
        int v;
        int nxt;
        int w;
    } node[MAX_N << 1];

    int head[MAX_N];
    int cnt;

    void create(int u, int v, int w);

    ll f[MAX_N][MAX_N];
    ll g[MAX_N];
    int siz[MAX_N];

    void dfs(int x);

   public:
    Solution() = default;
    ~Solution() = default;

    void solve();
};

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    C[0][0] = 1;
    for (int i = 1; i <= MAX_N - 50; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
            C[i][j] %= MOD;
        }
    }

    int T;
    read(T);
    while (T--) {
        auto solution = std::make_unique<Solution>();
        solution->solve();
    }

    return 0;
}

void Solution::create(int u, int v, int w) {
    node[++cnt].v = v;
    node[cnt].nxt = head[u];
    node[cnt].w = w;
    head[u] = cnt;
}

void Solution::dfs(int x) {
    siz[x] = f[x][1] = 1;
    for (int i = head[x]; i; i = node[i].nxt) {
        const int v = node[i].v, w = node[i].w;
        if (siz[v]) {
            continue;
        }
        dfs(v);

        memcpy(g, f[x], sizeof(f[x]));
        memset(f[x], 0, sizeof(f[x]));
        if (w == 1) {
            for (int j = 1; j <= siz[x]; j++) {
                for (int k = j; k < j + siz[v]; k++) {
                    f[x][k] += 1ll * C[siz[x] + siz[v] - k][siz[x] - j] *
                               C[k - 1][j - 1] % MOD * g[j] % MOD *
                               (f[v][siz[v]] - f[v][k - j] + MOD);
                    f[x][k] %= MOD;
                }
            }
        } else {
            for (int j = 1; j <= siz[x]; j++) {
                for (int k = j + 1; k <= j + siz[v]; k++) {
                    f[x][k] += 1ll * C[siz[x] + siz[v] - k][siz[x] - j] *
                               C[k - 1][j - 1] % MOD * g[j] % MOD * f[v][k - j];
                    f[x][k] %= MOD;
                }
            }
        }
        siz[x] += siz[v];
    }
    for (int i = 1; i <= siz[x]; i++) {
        f[x][i] += f[x][i - 1];
        f[x][i] %= MOD;
    }
}

void Solution::solve() {
    int n;
    read(n);
    for (int i = 1; i < n; i++) {
        int a, b;
        char ch;
        read(a);
        ch = getchar();
        while (ch != '<' and ch != '>') {
            ch = getchar();
        }
        read(b);

        a++;
        b++;
        create(a, b, ch == '<');
        create(b, a, ch == '>');
    }

    dfs(1);
    std::cout << f[1][n] << '\n';
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