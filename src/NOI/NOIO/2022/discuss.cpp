#include <bitset>
#include <cstdio>
#include <iostream>

constexpr int MAX_N = 5005;

class Solution {
   protected:
    std::bitset<MAX_N> b[MAX_N];

   public:
    Solution() = default;
    ~Solution() = default;

    void solve();
};

template <typename T>
T read();

int main() {
    freopen("discuss.in", "r", stdin);
    freopen("discuss.out", "w", stdout);

    int T = read<int>();
    while (T--) {
        auto* solution = new Solution();
        solution->solve();
        delete solution;
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}

void Solution::solve() {
    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        int k = read<int>();
        for (int j = 1; j <= k; j++) {
            int x = read<int>();
            b[i][x] = true;
        }
    }

    std::bitset<MAX_N> s1, s2, s3;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            s1 = b[i] & b[j];
            s2 = b[i] ^ s1;
            s3 = b[j] ^ s1;

            if (!s1.count() or !s2.count() or !s3.count()) {
                continue;
            }

            std::cout << "YES" << '\n' << i << ' ' << j << '\n';
            return;
        }
    }
    std::cout << "NO" << '\n';
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