#include <cstdio>
#include <iostream>

const int MAX_N = 50050;

int mob[MAX_N], pri[MAX_N], s[MAX_N];
bool vis[MAX_N];
int cnt;

int q(int x, int y, int k);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    mob[1] = 1;
    for (int i = 2; i <= 50000; i++) {
        if (!vis[i]) {
            pri[++cnt] = i;
            mob[i] = -1;
        }
        for (int j = 1; j <= cnt; j++) {
            if (i * pri[j] > 50000) {
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
    for (int i = 1; i <= 50000; i++) {
        s[i] = s[i - 1] + mob[i];
    }

    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        int a = read<int>(), b = read<int>(), c = read<int>(), d = read<int>(),
            k = read<int>();

        std::cout << q(b, d, k) - q(a - 1, d, k) - q(b, c - 1, k) +
                         q(a - 1, c - 1, k)
                  << '\n';
    }

    return 0;
}

int q(int x, int y, int k) {
    int res = 0, a = x / k, b = y / k, l, r;
    for (l = 1; l <= std::min(a, b); l = r + 1) {
        r = std::min(a / (a / l), b / (b / l));
        res += (a / l) * (b / l) * (s[r] - s[l - 1]);
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