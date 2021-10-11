#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 10000050;

int phi[MAX_N], pri[MAX_N];
bool vis[MAX_N];
int cnt;

void init(int n);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    init(10000000);

    int t = read<int>();
    while (t--) {
        int n = read<int>();
        std::cout << phi[n] << ' ' << 1ll * phi[n] * n / 2 << '\n';
    }

    return 0;
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
                phi[i * pri[j]] = pri[j] * (pri[j] - 1);
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