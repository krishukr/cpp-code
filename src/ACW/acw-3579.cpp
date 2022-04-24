#include <cstdio>
#include <iostream>
#include <memory>
#include <vector>

class Solution {
   private:
    constexpr static int MAX_N = 200050;

    int p[MAX_N], ans[MAX_N];
    bool vis[MAX_N];
    std::vector<int> cir;

    void dfs(int x);

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

void Solution::dfs(int x) {
    if (vis[x]) {
        return;
    }
    vis[x] = true;
    cir.push_back(x);
    dfs(p[x]);
}

void Solution::solve() {
    int n;
    read(n);
    for (int i = 1; i <= n; i++) {
        read(p[i]);
    }

    for (int i = 1; i <= n; i++) {
        if (vis[i]) {
            continue;
        }
        dfs(i);
        for (const auto& j : cir) {
            ans[j] = cir.size();
        }
        cir.clear();
    }

    for (int i = 1; i <= n; i++) {
        std::cout << ans[i] << ' ';
    }
    std::cout << '\n';
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