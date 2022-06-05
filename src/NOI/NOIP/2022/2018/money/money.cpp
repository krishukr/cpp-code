#include <climits>
#include <cstdio>
#include <iostream>
#include <memory>

constexpr int MAX_N = 25050;

class Solution {
   private:
    int a[MAX_N], f[MAX_N];

   public:
    Solution() {
        for (int i = 1; i < MAX_N; i++) {
            f[i] = (INT_MIN >> 1);
        }
    }
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
    freopen("money.in", "r", stdin);
    freopen("money.out", "w", stdout);
    std::ios::sync_with_stdio(false);

    int T;
    read(T);
    while (T--) {
        auto solution = std::make_unique<Solution>();
        solution->solve();
    }

    std::cout << std::flush;
    fclose(stdin);
    fclose(stdout);
    return 0;
}

void Solution::solve() {
    int n;
    read(n);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    for (int i = 1; i <= n; i++) {
        for (int j = a[i]; j < MAX_N; j++) {
            f[j] = std::max(f[j], f[j - a[i]] + 1);
        }
    }

    int r{};
    for (int i = 1; i <= n; i++) {
        if (f[a[i]] == 1) {
            r++;
        }
    }
    std::cout << r << '\n';
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