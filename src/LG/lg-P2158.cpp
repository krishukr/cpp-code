#include <cstdio>
#include <iostream>

constexpr int MAX_N = 40050;

struct ANS {
    bool vis[MAX_N];
    int pri[MAX_N], phi[MAX_N];
    int cnt;

    constexpr ANS() : vis(), pri(), phi(), cnt() {
        phi[1] = 1;
        for (int i = 2; i <= 40010; i++) {
            if (!vis[i]) {
                pri[++cnt] = i;
                phi[i] = i - 1;
            }
            for (int j = 1; j <= cnt; j++) {
                if (i * pri[j] > 40010) {
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
        for (int i = 2; i <= 40010; i++) {
            phi[i] += phi[i - 1];
        }
    }
};

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    constexpr auto ans = ANS();
    int n;
    read(n);
    if (n == 1) {
        std::cout << 0 << '\n';
    } else {
        std::cout << ans.phi[n - 1] * 2 + 1 << '\n';
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

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}