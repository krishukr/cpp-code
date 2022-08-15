#include <cstdio>
#include <iostream>
#include <queue>

using ll = long long;

constexpr int MAX_N = 100050;

int a[MAX_N];
std::queue<ll> q1, q2;

ll get();

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    read(n);
    for (int i = 1; i <= n; i++) {
        int x;
        read(x);
        a[x]++;
    }
    for (int i = 1; i <= 100001; i++) {
        while (a[i]) {
            a[i]--;
            q1.push(i);
        }
    }

    ll ans{};
    for (int i = 1; i < n; i++) {
        const auto s = get() + get();
        q2.push(s);
        ans += s;
    }
    std::cout << ans << '\n';

    return 0;
}

ll get() {
    ll r{};
    if (q2.empty() or (!q1.empty() and q1.front() < q2.front())) {
        r = q1.front();
        q1.pop();
    } else {
        r = q2.front();
        q2.pop();
    }
    return r;
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