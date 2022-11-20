#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using ll = long long;

constexpr int MAX_N = 250050;

int a[MAX_N], b[MAX_N];

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
        read(a[i]);
    }
    for (int i = 1; i <= n; i++) {
        read(b[i]);
    }

    ll crt{};
    std::priority_queue<std::pair<ll, int>> q;
    for (int i = 1; i <= n; i++) {
        crt += a[i];
        if (!q.empty() and crt <= b[i] and b[i] < q.top().first) {
            crt += q.top().first;
            q.pop();
        }
        if (crt >= b[i]) {
            crt -= b[i];
            q.push({b[i], i});
        }
    }

    std::vector<int> ans;
    while (!q.empty()) {
        ans.push_back(q.top().second);
        q.pop();
    }
    // std::sort(ans.begin(), ans.end());
    std::cout << ans.size() << '\n';
    for (const auto& i : ans) {
        std::cout << i << ' ';
    }
    std::cout << '\n';

    return 0;
}

template <typename T>
T read() {
    T x = 0, f = 1;
    char ch = getchar_unlocked();
    while (!isdigit(ch)) {
        if (ch == '-') f = -1;
        ch = getchar_unlocked();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getchar_unlocked();
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