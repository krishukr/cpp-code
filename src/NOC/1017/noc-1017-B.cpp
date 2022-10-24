#include <cstdio>
#include <iostream>
#include <memory>
#include <queue>

constexpr int MAX_N = 200050;
constexpr int INF = 0x3f3f3f3f;

class Solution {
    bool vis[MAX_N];
    int a[MAX_N], b[MAX_N], m[MAX_N];

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
    int n;
    read(n);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
        vis[a[i]] = true;
        b[a[i]] = i;
    }
    m[n + 1] = INF;
    for (int i = n; i >= 1; i--) {
        m[i] = std::min(m[i + 1], a[i] ? a[i] : INF);
    }

    std::priority_queue<int, std::vector<int>, std::greater<int>> q;
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            q.push(i);
        }
    }
    int rem{n};
    for (int i = 1; i < n; i++) {
        if (a[i] == 0) {
            if (m[i] > q.top()) {
                a[i] = q.top();
                q.pop();
            } else {
                a[i] = m[i];
                rem = b[a[i]];
                break;
            }
            continue;
        }
        if (a[i + 1]) {
            if (a[i] > a[i + 1]) {
                q.push(a[i]);
                rem = i;
                break;
            }
        } else {
            if (a[i] > q.top()) {
                q.push(a[i]);
                rem = i;
                break;
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (a[i] or i == rem) {
            continue;
        }
        a[i] = q.top();
        q.pop();
    }
    for (int i = 1; i <= n; i++) {
        if (i == rem) {
            continue;
        }
        std::cout << a[i] << ' ';
    }
    std::cout << '\n';
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