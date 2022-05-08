#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 2000050;

ll phi[MAX_N];
int pri[MAX_N];
bool vis[MAX_N];
int cnt;

void init(int n);

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
    init(n);

    ll ans{0};
    for (int i = 1, r; i <= n; i = r + 1) {
        r = n / (n / i);
        ans += ll(phi[r] - phi[i - 1]) * (n / i) * (n / i);
    }
    std::cout << (ans - 1ll * n * (n + 1) / 2) / 2 << '\n';

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

void init(int n) {
    phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) {
            pri[++cnt] = i;
            phi[i] = i - 1;
        }
        for (int j = 1; j <= cnt; j++) {
            if (i * pri[j] > n) {
                break;
            }
            vis[i * pri[j]] = true;
            if (!(i % pri[j])) {
                phi[i * pri[j]] = phi[i] * pri[j];
                break;
            } else {
                phi[i * pri[j]] = phi[i] * phi[pri[j]];
            }
        }
    }
    for (int i = 2; i <= n; i++) {
        phi[i] += phi[i - 1];
    }
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