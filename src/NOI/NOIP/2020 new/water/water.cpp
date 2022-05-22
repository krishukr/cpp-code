#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>

using ll = __int128_t;

constexpr int MAX_N = 100050;

std::vector<int> G[MAX_N];

int ind[MAX_N], oud[MAX_N];
ll p[MAX_N], q[MAX_N];
int n, m;

void topos();

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

std::ostream& operator<<(std::ostream& o, const ll& x) {
    if (x < 0) {
        return (o << '-' << (-x));
    }
    if (x > 9) {
        o << (x / 10);
    }
    return (o << (int)(x % 10));
}

int main() {
    freopen("water.in", "r", stdin);
    freopen("water.out", "w", stdout);
    std::ios::sync_with_stdio(false);

    read(n, m);
    for (int i = 1; i <= n; i++) {
        read(oud[i]);
        for (int j = 1; j <= oud[i]; j++) {
            int x;
            read(x);
            G[i].push_back(x);
            ind[x]++;
        }
    }

    topos();
    for (int i = 1; i <= n; i++) {
        if (oud[i] == 0) {
            std::cout << p[i] << ' ' << q[i] << '\n';
        }
    }

    std::cout << std::flush;

    fclose(stdin);
    fclose(stdout);
    return 0;
}

void topos() {
    std::queue<int> qu;
    for (int i = 1; i <= m; i++) {
        p[i] = q[i] = 1;
        qu.push(i);
    }

    while (!qu.empty()) {
        auto u = qu.front();
        qu.pop();

        for (const auto& v : G[u]) {
            --ind[v];
            if (q[v]) {
                const auto c = ll(1) * oud[u] * q[u];
                p[v] *= c;
                p[v] += p[u] * q[v];
                q[v] *= c;

            } else {
                p[v] = p[u];
                q[v] = ll(1) * q[u] * oud[u];
            }
            const auto g = std::__gcd(p[v], q[v]);
            p[v] /= g;
            q[v] /= g;

            if (!ind[v]) {
                qu.push(v);
            }
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