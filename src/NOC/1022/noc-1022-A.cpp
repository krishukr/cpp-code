#include <cstdio>
#include <iostream>

using ull = unsigned long long;
using lll = __int128_t;

constexpr int N = 3e7 + 10;

int n, A, B, C, u[N], v[N], w[N];

ull Rand(ull& k1, ull& k2) {
    ull k3 = k1, k4 = k2;
    k1 = k4;
    k3 ^= (k3 << 23);
    k2 = k3 ^ k4 ^ (k3 >> 17) ^ (k4 >> 26);
    return k2 + k4;
}

void GetData() {
    ull x, y;
    std::cin >> n >> A >> B >> C >> x >> y;
    for (int i = 1; i <= n; i++) {
        u[i] = Rand(x, y) % A + 1;
        v[i] = Rand(x, y) % B + 1;
        w[i] = Rand(x, y) % C + 1;
        if (Rand(x, y) % 3 == 0) u[i] = A;
        if (Rand(x, y) % 3 == 0) v[i] = B;
        if ((u[i] != A) && (v[i] != B)) w[i] = C;
    }
}

std::ostream& operator<<(std::ostream& o, const lll& a) {
    if (a < 0) {
        return (o << '-' << (-a));
    }
    if (a > 9) {
        o << (a / 10);
    }
    return (o << (int)(a % 10));
}

int a[N], b[N], c[N], d[N];

int main() {
    std::ios::sync_with_stdio(false);

    GetData();

    for (int i = 1; i <= n; i++) {
        if (w[i] == C) {
            a[u[i]] = std::max(a[u[i]], v[i]);
        } else if (u[i] == A) {
            d[w[i]] = std::max(d[w[i]], v[i]);
        } else if (v[i] == B) {
            c[w[i]] = std::max(c[w[i]], u[i]);
        }
    }
    for (int i = A; i >= 1; i--) {
        a[i] = std::max(a[i], a[i + 1]);
    }
    for (int i = C; i >= 1; i--) {
        c[i] = std::max(c[i], c[i + 1]);
    }
    for (int i = C; i >= 1; i--) {
        d[i] = std::max(d[i], d[i + 1]);
    }

    for (int i = 1, t = A; i <= B; i++) {
        while (t and a[t] < i) {
            t--;
        }
        b[i] = t;
    }

    lll ans{}, tot{};
    for (int i = 1, tx = A, ty = B; i <= C; i++) {
        while (tx > c[i]) {
            tot += B - ty - std::max(0, a[tx] - ty);
            tx--;
        }
        while (ty > d[i]) {
            tot += A - tx - std::max(0, b[ty] - tx);
            ty--;
        }
        ans += tot;
    }
    std::cout << (lll)1 * A * B * C - ans << '\n';

    return 0;
}