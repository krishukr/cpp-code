#include <algorithm>
#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 100050;
const int MOD = 1e9 + 7;

struct Node {
    int x;
    int y;

    bool operator<(const Node &n) const {
        return x < n.x or (x == n.x and y < n.x);
    }
} node[MAX_N];

ll fact[MAX_N], p[MAX_N], dp[MAX_N];

ll quick_pow(ll a, ll b);

ll combination(ll n, ll m);

ll q(int a, int b);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>(), c = read<int>();

    fact[0] = 1;
    for (int i = 1; i <= n * 2; i++) {
        fact[i] = (i * fact[i - 1]) % MOD;
    }
    for (int i = 1; i <= c; i++) {
        node[i].x = read<int>();
        node[i].y = read<int>();
    }

    node[c + 1].x = n;
    node[c + 1].y = n;
    std::sort(node + 1, node + c + 2);

    for (int i = 1; i <= c + 1; i++) {
        for (int j = 1; j < i; j++) {
            p[i] += dp[j] * q(j, i) % MOD;
        }
        dp[i] = (q(0, i) - p[i] + MOD) % MOD;
    }
    std::cout << dp[c + 1] << '\n';

    return 0;
}

ll quick_pow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % MOD;
        }
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}

ll combination(ll n, ll m) {
    if (n < m) {
        return 0;
    } else {
        return fact[n] * quick_pow(fact[m], MOD - 2) % MOD *
               quick_pow(fact[n - m], MOD - 2) % MOD;
    }
}

ll q(int a, int b) {
    int x = node[b].x - node[a].x, y = node[b].y - node[a].y;
    if (x < 0 or y < 0) {
        return 0;
    }
    if (node[b].y + 1 - node[a].x < 0 or node[b].x + 1 - node[a].y < 0) {
        return combination(x + y, x);
    }

    return (combination(x + y, x) -
            combination(x + y, node[b].y - node[a].x - 1) + MOD) %
           MOD;
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