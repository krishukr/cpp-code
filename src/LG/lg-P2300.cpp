#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 200050;

ll s[MAX_N], l[MAX_N];
int q[MAX_N], dp[MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    for (int i = 1; i <= n; i++) {
        int x = read<int>();
        s[i] = s[i - 1] + x;
    }

    int h = 0, t = 1;
    for (int i = 1; i <= n; i++) {
        while (h + 1 < t and s[q[h + 1]] + l[q[h + 1]] <= s[i]) {
            h++;
        }
        dp[i] = dp[q[h]] + 1;
        l[i] = s[i] - s[q[h]];
        while (h < t and s[i] + l[i] <= s[q[t - 1]] + l[q[t - 1]]) {
            t--;
        }
        q[t++] = i;
    }

    std::cout << n - dp[n] << '\n';

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