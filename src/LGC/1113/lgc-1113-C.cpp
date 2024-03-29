#include <algorithm>
#include <cstdio>
#include <functional>
#include <iostream>
#include <memory>
#include <queue>
#include <vector>

using ll = long long;

template <typename T>
using pq = std::priority_queue<T, std::vector<T>, std::greater<T>>;

constexpr int MAX_N = 100050;

class Solution {
    struct S {
        int a;
        int b;
    } s[MAX_N];

   public:
    Solution() = default;
    ~Solution() = default;

    void solve();
};

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int T;
    read(T);
    while (T--) {
        auto solution = std::make_unique<Solution>();
        solution->solve();
    }

    return 0;
}

void Solution::solve() {
    int n, _first;
    read(n, _first);
    for (int i = 1; i <= n; i++) {
        read(s[i].a);
    }
    for (int i = 1; i <= n; i++) {
        read(s[i].b);
    }

    std::sort(s + 1, s + n + 1, [](const S& x, const S& y) {
        return x.a == y.a ? x.b < y.b : x.a > y.a;
    });

    pq<int> q;
    for (int i = 1; i <= n; i++) {
        q.push(s[i].b);
        const auto m = (i + _first) / 2;
        if (q.size() > m) {
            q.pop();
        }
    }

    ll ans{};
    while (!q.empty()) {
        ans += q.top();
        q.pop();
    }
    std::cout << ans << '\n';
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