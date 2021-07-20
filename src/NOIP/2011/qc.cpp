#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>

const int MAX_N = 200050;

typedef long long ll;

ll w[MAX_N], v[MAX_N];
ll ql[MAX_N], qr[MAX_N];
ll q[MAX_N], sum[MAX_N];

template <typename T>
T read();

int main() {
    freopen("qc.in", "r", stdin);
    freopen("qc.out", "w", stdout);

    ll l = 0, r, min = LLONG_MAX;
    ll n = read<ll>(), m = read<ll>(), s = read<ll>();

    for (int i = 1; i <= n; i++) {
        w[i] = read<ll>();
        v[i] = read<ll>();
        r = std::max(r, w[i]);
    }
    for (int i = 1; i <= m; i++) {
        ql[i] = read<ll>();
        qr[i] = read<ll>();
    }

    while (l <= r) {
        ll ans = 0, mid = (l + r) / 2;
        for (int i = 1; i <= n; i++) {
            if (w[i] > mid) {
                q[i] = q[i - 1] + 1;
                sum[i] = sum[i - 1] + v[i];
            } else {
                q[i] = q[i - 1];
                sum[i] = sum[i - 1];
            }
        }
        for (int i = 1; i <= m; i++) {
            ans += (q[qr[i]] - q[ql[i] - 1]) * (sum[qr[i]] - sum[ql[i] - 1]);
        }
        ans = s - ans;
        if (ans < 0) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
        min = std::min(min, std::abs(ans));
    }

    std::cout << min << '\n';

    fclose(stdin);
    fclose(stdout);
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