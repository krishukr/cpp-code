#include <cstdio>
#include <cstring>
#include <iostream>

typedef long long ll;
typedef unsigned long long ull;

const int MAX_N = 2000050;
const ull HB = 131;

int vis[31], cr[31];

int a[MAX_N], b[MAX_N], c[MAX_N], s1[MAX_N], s2[MAX_N];
ull h1[MAX_N], h2[MAX_N];

std::string s;

template <typename T>
T read();

int main() {
    // std::ios::sync_with_stdio(false);

    h2[0] = 1;
    for (int i = 1; i < MAX_N; i++) {
        h2[i] = h2[i - 1] * HB;
    }
    int T = read<int>();

    while (T--) {
        std::cin >> s;
        int n = s.length();

        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
        memset(s2, 0, sizeof(s1));
        memset(vis, 0, sizeof(vis));
        memset(cr, 0, sizeof(cr));

        ll ans = 0;
        for (int i = 1; i <= n; i++) {
            c[i] = s[i - 1] - 96;
            cr[c[i]] ^= 1;

            if (cr[c[i]]) {
                s1[i] = s1[i - 1] + 1;
            } else {
                s1[i] = s1[i - 1] - 1;
            }
            a[i] = s1[i];
        }

        memset(cr, 0, sizeof(cr));
        for (int i = n; i > 0; i--) {
            cr[c[i]] ^= 1;

            if (cr[c[i]]) {
                s2[i] = s2[i + 1] + 1;
            } else {
                s2[i] = s2[i + 1] - 1;
            }
            b[i] = s2[i];
        }

        for (int i = 1; i <= n; i++) {
            h1[i] = h1[i - 1] * HB + 1ull * c[i];
        }

        for (int i = 2; i <= n; i++) {
            for (int j = a[i - 1]; j <= 26; j++) {
                vis[j]++;
            }
            for (int j = i; j < n and h1[i] == h1[j] - h1[j - i] * h2[i];
                 j += i) {
                ans += vis[b[j + 1]];
            }
        }

        std::cout << ans << '\n';
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