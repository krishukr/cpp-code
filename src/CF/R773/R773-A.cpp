#include <cstdio>
#include <iostream>

template <typename T>
T read();

class Solution {
   private:
    int x[10];
    int y[10];

   public:
    Solution() = default;
    ~Solution() = default;

    void solve() {
        for (int i = 1; i <= 3; i++) {
            x[i] = read<int>();
            y[i] = read<int>();
        }

        int m = 0x3f3f3f3f;
        for (int i = 1; i <= 3; i++) {
            m = std::min(m, y[i]);
        }

        int ans = 0;
        for (int i = 1; i <= 3; i++) {
            for (int j = 1; j <= 3; j++) {
                if (i == j or y[i] == m or y[j] == m) {
                    continue;
                }
                if (y[i] == y[j]) {
                    ans += std::abs(x[i] - x[j]);
                }
            }
        }

        std::cout << ans / 2 << '\n';
    }
};

int main() {
    std::ios::sync_with_stdio(false);

    int T = read<int>();
    while (T--) {
        auto* solution = new Solution();
        solution->solve();
        delete solution;
    }

    return 0;
}

template <typename T>
T read() {
    T x = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    return x * f;
}