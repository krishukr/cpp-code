#include <cstdio>
#include <iostream>

#define int long long

const int MAX_N = 50050;

int mob[MAX_N], pri[MAX_N], s[MAX_N], f[MAX_N];
bool vis[MAX_N];
int cnt;

void init(int n);

int q(int a, int b);

template <typename T>
T read();

signed main() {
    std::ios::sync_with_stdio(false);

    init(50000);

    int t = read<int>();
    while (t--) {
        int n = read<int>(), m = read<int>();
        std::cout << q(n, m) << '\n';
    }

    return 0;
}

void init(int n) {
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
        s[i] = s[i - 1] + mob[i];
    }

    for (int i = 1; i <= n; i++) {
        int l, r;
        for (l = 1; l <= i; l = r + 1) {
            r = i / (i / l);
            f[i] += (r - l + 1) * (i / l);
        }
    }
}

int q(int a, int b) {
    int l, r, res = 0;
    for (int l = 1; l <= std::min(a, b); l = r + 1) {
        r = std::min(a / (a / l), b / (b / l));
        res += (s[r] - s[l - 1]) * f[a / l] * f[b / r];
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