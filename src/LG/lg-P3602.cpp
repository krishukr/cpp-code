#include <algorithm>
#include <cstdio>
#include <iostream>
#include <iterator>
#include <set>
#include <utility>

constexpr int MAX_N = 500050;

std::pair<int, int> a[MAX_N], b[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m;
    read(n, m);
    for (int i = 1; i <= n; i++) {
        read(a[i].first, a[i].second);
    }
    for (int i = 1; i <= m; i++) {
        read(b[i].first, b[i].second);
    }
    std::sort(a + 1, a + n + 1);
    std::sort(b + 1, b + m + 1);

    std::multiset<int> s;
    int ans{n};
    for (int i = 1, j = 1; i <= m; i++) {
        for (; j <= n and a[j].first <= b[i].first; j++) {
            s.insert(a[j].second);
        }
        while (!s.empty() and *s.begin() < b[i].first) {
            s.erase(s.begin());
        }
        while (s.size() > b[i].second) {
            s.erase(std::prev(s.end()));
            ans--;
        }
    }
    std::cout << ans << '\n';

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