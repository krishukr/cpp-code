#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 10000050;

ll mob[MAX_N], pri[MAX_N], s[MAX_N], g[MAX_N];
bool vis[MAX_N];
int cnt;

void init(int n);

ll q(int x, int y);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    init(10000000);

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
    for (int i = 1; i <= cnt; i++) {
        for (int j = 1; j * pri[i] <= n; j++) {
            g[j * pri[i]] += mob[j];
        }
    }
    for (int i = 1; i <= n; i++) {
        s[i] = s[i - 1] + g[i];
    }
}

ll q(int x, int y) {
    ll res = 0, l, r;
    for (l = 1; l <= std::min(x, y); l = r + 1) {
        r = std::min(x / (x / l), y / (y / l));
        res += (x / l) * (y / l) * (s[r] - s[l - 1]);
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