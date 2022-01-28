#include <algorithm>
#include <cstdio>
#include <iostream>

typedef long long ll;

const int MAX_N = 1000005;
const int MOD = 99999997;

struct Match {
    int a;
    int b;

    bool operator<(const Match &m) const { return a < m.a; }
} m[MAX_N], d[MAX_N];

ll x[MAX_N], p[MAX_N];
ll ans = 0, n;

void merge_sort(int l, int r);

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    n = read<ll>();
    for (int i = 1; i <= n; i++) {
        m[i].a = read<int>();
        m[i].b = i;
    }
    for (int i = 1; i <= n; i++) {
        d[i].a = read<int>();
        d[i].b = i;
    }
    std::sort(m + 1, m + n + 1);
    std::sort(d + 1, d + n + 1);

    for (int i = 1; i <= n; i++) {
        x[d[i].b] = m[i].b;
    }
    merge_sort(1, n);

    std::cout << ans << '\n';

    return 0;
}

void merge_sort(int l, int r) {
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    merge_sort(l, mid);
    merge_sort(mid + 1, r);

    int i = l, j = mid + 1, k = l;
    while (i <= mid and j <= r) {
        if (x[i] <= x[j]) {
            p[k] = x[i];
            i++;
            k++;
        } else {
            p[k] = x[j];
            j++;
            k++;
            ans = (ans + mid - i + 1) % MOD;
        }
    }

    while (i <= mid) {
        p[k] = x[i];
        i++;
        k++;
    }
    while (j <= r) {
        p[k] = x[j];
        j++;
        k++;
    }
    for (int i = l; i <= r; i++) {
        x[i] = p[i];
    }
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