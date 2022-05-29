#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>

typedef __int128 ll;

const int MAX_N = 100050;

std::vector<int> G[MAX_N];
int ind[MAX_N], oud[MAX_N];
ll p[MAX_N], q[MAX_N];
int n, m;

template <typename T>
T read();

ll gcd(ll a, ll b);

void put(ll x);

void topological();

int main() {
    std::ios::sync_with_stdio(false);

    n = read<int>(), m = read<int>();

    for (int i = 1; i <= n; i++) {
        oud[i] = read<int>();

        for (int j = 1; j <= oud[i]; j++) {
            int x = read<int>();
            G[i].push_back(x);
            ind[x]++;
        }
    }

    topological();

    for (int i = 1; i <= n; i++) {
        if (!oud[i]) {
            // std::cout << p[i] << ' ' << q[i] << '\n';
            put(p[i]);
            putchar(' ');
            put(q[i]);
            putchar('\n');
        }
    }

    return 0;
}

ll gcd(ll a, ll b) { return (!b ? a : gcd(b, a % b)); }

void put(ll x) {
    if (x >= 10) {
        put(x / 10);
    }
    putchar((x % 10) + 48);
}

void topological() {
    std::queue<int> que;
    for (int i = 1; i <= m; i++) {
        p[i] = q[i] = 1;
        que.push(i);
    }

    while (!que.empty()) {
        int h = que.front();
        que.pop();

        for (int i = 0; i < oud[h]; i++) {
            int v = G[h][i];
            --ind[v];

            if (!q[v]) {
                p[v] = p[h];
                q[v] = 1ll * q[h] * oud[h];

                ll g = gcd(p[v], q[v]);
                p[v] /= g;
                q[v] /= g;
            } else {
                ll c = 1ll * oud[h] * q[h];
                p[v] *= c;
                p[v] += p[h] * q[v];
                q[v] *= c;

                ll g = gcd(p[v], q[v]);
                p[v] /= g;
                q[v] /= g;
            }

            if (!ind[v]) {
                que.push(v);
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