#include <algorithm>
#include <cstdio>
#include <iostream>

typedef long long ll;

const ll MOD = 1e9 + 7;
const int MAX_N = 100050;

int a[MAX_N], b[MAX_N];
int ans, cnt;

ll quick_pow(ll a, ll b);

template <typename T>
T read();

int main() {
    freopen("mex.in", "r", stdin);
    freopen("mex.out", "w", stdout);

    int n = read<int>();
    ans = n;

    for (int i = 0; i < n; i++) {
        a[i] = read<int>();
    }
    for (int i = 0; i < n; i++) {
        b[i] = read<int>();
    }

    for (int i = 0; i < n; i++) {
        if (a[i] < b[i]) {
            std::swap(a[i], b[i]);
            cnt--;
        }
    }
    for (int i = 0; i < n; i++) {
        while (a[i] > 0 and a[i] < n and a[a[i] - 1] != a[i]) {
            std::swap(a[a[i] - 1], a[i]);
        }
    }
    for (int i = 0; i < n; i++) {
        if (a[i] != i + 1) {
            ans = i + 1;
            break;
        }
    }

    std::sort(a, a + n);
    std::sort(b, b + n);

    if (b[0] == 0 and a[0] != b[0]) {
        ans = 0;
    }

    for (int i = 0; i < n; i++) {
        if (a[i] >= b[i]) {
            cnt++;
        }
    }

    std::cout << ans << ' ' << quick_pow(2, cnt) << '\n';

    fclose(stdin);
    fclose(stdout);
    return 0;
}

ll quick_pow(ll a, ll b) {
    ll res = 1;
    while (b) {
        if (b & 1) {
            res = res * a % MOD;
        }
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
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
