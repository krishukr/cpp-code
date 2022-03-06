#include <cstdio>
#include <iostream>

template <typename T>
T read();

class Solution {
   public:
    void solve() {
        int n = read<int>();
        auto* a = new int[n + 5];
        bool flag = false;

        for (int i = 1; i <= n; i++) {
            a[i] = read<int>();
        }

        int p1 = 1, p2 = n;
        for (int i = 1; i <= n; i++) {
            if (!a[i]) {
                p1 = i - 1;
                flag = true;
                break;
            }
        }
        for (int i = n; i >= 1; i--) {
            if (!a[i]) {
                p2 = i + 1;
                break;
            }
        }

        std::cout << (flag ? p2 - p1 : 0) << '\n';
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
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = x * 10 + ch - 48;
        ch = getchar();
    }
    return x * f;
}