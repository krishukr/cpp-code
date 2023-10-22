#include <cstdio>
#include <iostream>
#include <memory>

constexpr int MAX_N = 200050;
constexpr int MOD = 3;

class Solution {
    int s[MAX_N];

    int bc(int n, int r);

    int lucas(int n, int r);

   public:
    void solve();
};

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

template <>
char read();

int main() {
    std::ios::sync_with_stdio(false);

    int T;
    read(T);
    while (T--) {
        auto solution = std::make_unique<Solution>();
        solution->solve();
    }

    std::cout << std::flush;
    return 0;
}

int Solution::bc(int n, int r) {
    int res{1};
    for (int i = n; i > n - r; i--) {
        res = res * i % MOD;
    }
    for (int i = 1; i <= r; i++) {
        res = res * i % MOD;
    }
    return res;
}

int Solution::lucas(int n, int r) {
    if (!r) {
        return 1;
    }
    return bc(n % MOD, r % MOD) * lucas(n / MOD, r / MOD) % MOD;
}

void Solution::solve() {
    int n;
    read(n);
    for (int i = 0; i < n; i++) {
        s[i] = read<char>() - 'A';
    }

    int ans{};
    for (int i = 0; i < n; i++) {
        ans += s[i] * lucas(n - 1, i) % MOD;
    }
    ans %= MOD;
    std::cout << (char)(n & 1 ? ans + 'A' : (MOD - ans) % MOD + 'A') << '\n';
}

template <typename T>
T read() {
    T x{}, f{1};
    int ch = getchar_unlocked();
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

template <>
char read() {
    int ch = getchar_unlocked();
    while (ch != 'A' and ch != 'B' and ch != 'C') {
        ch = getchar_unlocked();
    }
    return ch;
}