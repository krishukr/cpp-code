#include <cstdio>
#include <iostream>

using ll = long long;

constexpr int MAX_N = 100050;

int pri[MAX_N], mob[MAX_N];
bool vis[MAX_N];
int cnt;

void init(const int& n);

ll q(int x, int y);

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
    ll ans{};
    for (int i = 1; i <= n; i++) {
        ans += q(n / i, i) * i;
    }
    std::cout << ans << '\n';

    return 0;
}

void init(const int& n) {
    mob[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (!vis[i]) {
            pri[++cnt] = i;
            mob[i] = -1;
        }
        for (int j = 1; j <= cnt; j++) {
            if (i * pri[j] > n) {
                break;
            }

            vis[i * pri[j]] = true;
            if (!(i % pri[j])) {
                mob[i * pri[j]] = 0;
                break;
            }
            mob[i * pri[j]] = -mob[i];
        }
    }
    for (int i = 1; i <= n; i++) {
        mob[i] += mob[i - 1];
    }
}

ll q(int x, int y) {
    ll res = 0, l, r;
    for (l = 1; l <= x; l = r + 1) {
        r = x / (x / l);
        res += (x / l) * (x / l) * (mob[r] - mob[l - 1]);
    }
    return res;
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