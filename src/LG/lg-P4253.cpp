#include <climits>
#include <cstdio>
#include <iostream>
#include <vector>

using ll = long long;

constexpr int MAX_N = 200050;
constexpr ll INF = LLONG_MAX >> 1;

int a[MAX_N], b[MAX_N];
ll dep[MAX_N];
std::vector<ll> f[MAX_N], g[MAX_N], dis[MAX_N];
int n;

void dfs(int x);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    read(n);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    for (int i = 2; i <= n; i++) {
        read(b[i]);
    }

    dfs(1);
    ll ans = INF;
    for (const auto& i : g[1]) {
        ans = std::min(ans, i);
    }
    std::cout << ans << '\n';

    return 0;
}

void dfs(int x) {
    dep[x] = dep[x >> 1] + b[x];
    if ((x << 1) <= n) {
        dfs(x << 1);
        int s = f[x << 1].size();
        if ((x << 1) + 1 <= n) {
            dfs((x << 1) + 1);
            ll a1{INF}, pa1{INF}, a2{INF}, pa2{INF};
            for (int i = 0; i < f[x].size(); i++) {
                if (i < s) {
                    a1 = std::min(
                        a1,
                        f[x << 1][i] + 1ll * a[x << 1] * b[x << 1] +
                            a[(x << 1) + 1] * (b[(x << 1) + 1] + dis[x][i]));
                    pa1 = std::min(pa1,
                                   g[x << 1][i] +
                                       1ll * a[(x << 1) + 1] * b[(x << 1) + 1] +
                                       a[x] * dis[x][i]);
                } else {
                    a2 = std::min(a2,
                                  f[(x << 1) + 1][i - s] +
                                      1ll * a[(x << 1) + 1] * b[(x << 1) + 1] +
                                      a[x << 1] * (b[x << 1] + dis[x][i]));
                    pa2 = std::min(pa2, g[(x << 1) + 1][i - s] +
                                            1ll * a[x << 1] * b[x << 1] +
                                            a[x] * dis[x][i]);
                }
            }
            for (int i = 0; i < f[x].size(); i++) {
                if (i < s) {
                    f[x][i] = a2 + f[x << 1][i];
                    g[x][i] = std::min(f[x][i], pa2 + f[x << 1][i]);
                } else {
                    f[x][i] = a1 + f[(x << 1) + 1][i - s];
                    g[x][i] = std::min(f[x][i], pa1 + f[(x << 1) + 1][i - s]);
                }
            }
        } else {
            for (int i = x; i >= 1; i >>= 1) {
                f[i].push_back(0);
                g[i].push_back(0);
                dis[i].push_back(dep[x] - dep[i]);
            }
            f[x][0] = 1ll * a[x << 1] * b[x << 1];
            g[x][0] = INF;
            f[x][1] = INF;
            g[x][1] = 1ll * a[x] * b[x << 1];
        }
    } else {
        for (int i = x; i >= 1; i >>= 1) {
            f[i].push_back(0);
            g[i].push_back(0);
            dis[i].push_back(dep[x] - dep[i]);
        }
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

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}