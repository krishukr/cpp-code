#include <climits>
#include <cstdio>
#include <iostream>
#include <queue>

typedef long long ll;

constexpr int MAX_N = 1050;
constexpr int MAX_M = 1000050;

ll a[MAX_N][MAX_N];
ll ra[MAX_M], ca[MAX_M];

std::priority_queue<ll> rq, cq;

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    ll n, m, k, p;
    read(n, m, k, p);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            read(a[i][j]);
        }
    }
    for (int i = 1; i <= n; i++) {
        ll add = 0;
        for (int j = 1; j <= m; j++) {
            add += a[i][j];
        }
        rq.push(add);
    }
    for (int i = 1; i <= m; i++) {
        ll add = 0;
        for (int j = 1; j <= n; j++) {
            add += a[j][i];
        }
        cq.push(add);
    }
    for (int i = 1; i <= k; i++) {
        auto t = rq.top();
        rq.pop();
        ra[i] = ra[i - 1] + t;
        t -= m * p;
        rq.push(t);
    }
    for (int i = 1; i <= k; i++) {
        auto t = cq.top();
        cq.pop();
        ca[i] = ca[i - 1] + t;
        t -= n * p;
        cq.push(t);
    }

    ll ans = LLONG_MIN;
    for (int i = 0; i <= k; i++) {
        ans = std::max(ans, ca[k - i] + ra[i] - 1ll * i * (k - i) * p);
    }
    std::cout << ans << '\n';

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

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}