#include <cstdio>
#include <cstring>
#include <iostream>

constexpr int MAX_N = 1000050;

char s[MAX_N];
int re[MAX_N];
bool ans[MAX_N];
int n;

void manacher();

int main() {
    std::ios::sync_with_stdio(false);

    int T;
    std::cin >> T;
    while (T--) {
        std::cin >> (s + 1);
        n = std::strlen(s + 1);
        s[0] = 'A';
        s[n + 1] = 'B';
        manacher();

        for (int i = n; i >= 1; i--) {
            ans[i] = false;
            if (i + re[i] == n) {
                ans[i] = true;
            } else if (ans[i + re[i]] and i - re[i] == 1) {
                ans[i] = true;
            }
        }

        for (int i = 1; i <= n; i++) {
            if (ans[i]) {
                std::cout << i << ' ';
            }
        }
        std::cout << '\n';
    }

    return 0;
}

void manacher() {
    int r = 0, mid = 0;
    for (int l = 1; l <= n; l++) {
        re[l] = 0;
        if (l < r) {
            re[l] = std::min(r - l, re[mid + mid - l]);
        }
        while (s[l + re[l] + 1] == s[l - re[l] - 1]) {
            re[l]++;
        }
        if (r < l + re[l]) {
            r = l + re[l];
            mid = l;
        }
    }
}