#include <cstdio>
#include <iostream>
#include <queue>

typedef long long ll;

const int MAX_N = 100050;

ll g[MAX_N];
ll ans;
std::queue<ll> q;
std::queue<ll> l;

template <typename T>
T gcd(T x, T y);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    g[0] = -1;

    for (int i = 1; i <= n; i++) {
        g[i] = read<ll>();
        int lst = 0;

        while (!q.empty()) {
            int p = q.front();
            q.pop();
            g[p] = gcd(g[p], g[i]);
            ans = std::max(ans, g[p] * (i - p + 1));

            if (g[p] == g[lst]) {
                continue;
            }
            l.push(p);
            lst = p;
        }
        ans = std::max(ans, g[i]);

        while (!l.empty()) {
            q.push(l.front());
            l.pop();
        }
        if (g[lst] != g[i]) {
            q.push(i);
        }
    }

    std::cout << ans << '\n';

    return 0;
}

template <typename T>
T gcd(T x, T y) {
    do {
        T t = x % y;
        x = y;
        y = t;
    } while (y);
    return x;
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