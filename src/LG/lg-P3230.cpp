#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>

typedef long long ll;

const int MAX_N = 15;
const int MOD = 1e9 + 7;

ll a[MAX_N], tmp[MAX_N];
std::map<ll, ll> vis;

ll cal(int x);

ll dfs(int x, int d);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();

    for (int i = 1; i <= n; i++) {
        a[i] = read<ll>();
    }
    std::sort(a + 1, a + n + 1,
              [](const ll& x, const ll& y) -> bool { return x > y; });

    std::cout << dfs(1, n) << '\n';

    return 0;
}

ll cal(int x) {
    ll res = x;

    for (int i = 1; i <= x; i++) {
        tmp[i] = a[i];
    }
    std::sort(tmp + 1, tmp + x + 1,
              [](const ll& x, const ll& y) -> bool { return x > y; });

    for (int i = 1; i <= x; i++) {
        res += res * 27 + tmp[i];
    }
    return res;
}

ll dfs(int x, int d) {
    if (a[d] > 3 * (d - x)) {
        return -114514;
    }
    ll res = 0;

    if (x == d) {
        if (d == 1) {
            return 1;
        } else {
            ll hsh = cal(d - 1);
            if (vis[hsh]) {
                return vis[hsh];
            } else {
                return vis[hsh] = dfs(1, d - 1);
            }
        }
    }

    if (a[d] >= 3) {
        a[d] -= 3;
        ll tmp = dfs(x + 1, d);
        if (tmp != -114514) {
            res += tmp;
            res %= MOD;
        }
        a[d] += 3;
    }

    if (a[x] and a[d]) {
        a[x] -= 1;
        a[d] -= 1;
        ll tmp = dfs(x + 1, d);
        if (tmp != -114514) {
            res += tmp;
            res %= MOD;
        }
        a[x] += 1;
        a[d] += 1;
    }

    if (a[x] >= 3) {
        a[x] -= 3;
        ll tmp = dfs(x + 1, d);
        if (tmp != -114514) {
            res += tmp;
            res %= MOD;
        }
        a[x] += 3;
    }

    return res ? res : -114514;
}

template <typename T>
T read() {
    T x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-') f = -114514;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    return x * f;
}