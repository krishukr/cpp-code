#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>

using pir = std::pair<int, int>;

template <typename T>
using pgq = std::priority_queue<T, std::vector<T>, std::greater<T>>;

constexpr int MAX_N = 100050;

pir p1[MAX_N], p2[MAX_N];
int r1[MAX_N], r2[MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    freopen("airport.in", "r", stdin);
    freopen("airport.out", "w", stdout);
    std::ios::sync_with_stdio(false);

    int n, m1, m2;
    read(n, m1, m2);
    for (int i = 1; i <= m1; i++) {
        int a, b;
        read(a, b);
        p1[i] = {a, b};
    }
    for (int i = 1; i <= m2; i++) {
        int a, b;
        read(a, b);
        p2[i] = {a, b};
    }
    std::sort(p1 + 1, p1 + m1 + 1);
    std::sort(p2 + 1, p2 + m2 + 1);

    {
        pgq<pir> q1;
        pgq<int> q2;
        for (int i = 1; i <= n; i++) {
            q2.push(i);
        }
        for (int i = 1; i <= m1; i++) {
            while (!q1.empty() and q1.top().first <= p1[i].first) {
                q2.push(q1.top().second);
                q1.pop();
            }
            if (q2.empty()) {
                continue;
            }
            auto e = q2.top();
            q2.pop();
            r1[e]++;
            q1.push({p1[i].second, e});
        }
        for (int i = 1; i < n; i++) {
            r1[i + 1] += r1[i];
        }
    }
    {
        pgq<pir> q1;
        pgq<int> q2;
        for (int i = 1; i <= n; i++) {
            q2.push(i);
        }
        for (int i = 1; i <= m2; i++) {
            while (!q1.empty() and q1.top().first <= p2[i].first) {
                q2.push(q1.top().second);
                q1.pop();
            }
            if (q2.empty()) {
                continue;
            }
            auto e = q2.top();
            q2.pop();
            r2[e]++;
            q1.push({p2[i].second, e});
        }
        for (int i = 1; i < n; i++) {
            r2[i + 1] += r2[i];
        }
    }

    int ans{};
    for (int i = 0; i <= n; i++) {
        ans = std::max(ans, r1[i] + r2[n - i]);
    }
    std::cout << ans << '\n';

    std::cout << std::flush;
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

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}