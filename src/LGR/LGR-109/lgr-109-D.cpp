// 非赛时

#include <cstdio>
#include <iostream>
#include <memory>

class Solution {
   private:
    constexpr static int MAX_N = 100050;

    int deg[MAX_N];

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
    for (int i = 1; i < n; i++) {
        int x, y;
        read(x, y);
        deg[x]++;
        deg[y]++;
    }

    for (int i = 1; i <= n; i++) {
        if (!(deg[i] & 1)) {
            std::cout << "Hifuu" << '\n';
            return;
        }
    }
    std::cout << "Luna" << '\n';
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