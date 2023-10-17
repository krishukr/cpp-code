#include <cstdio>
#include <iostream>

constexpr int MAX_N = 200050;
constexpr int MOD = 92084931;

int s[MAX_N], a[MAX_N];
long long ans;

void merge_sort(int l, int r);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int n, m;
    read(n, m);
    for (int i = 1; i <= n; i++) {
        read(s[i]);
        s[i] = s[i] + s[i - 1] - m;
    }
    merge_sort(0, n);
    std::cout << ans % MOD << '\n';

    std::cout << std::flush;
    return 0;
}

void merge_sort(int l, int r) {
    if (l >= r) {
        return;
    }
    const auto mid = (l + r) >> 1;
    merge_sort(l, mid);
    merge_sort(mid + 1, r);

    int i, j, k;
    for (i = k = l, j = mid + 1; i <= mid and j <= r; k++) {
        if (s[i] >= s[j]) {
            a[k] = s[i++];
        } else {
            a[k] = s[j++];
            ans += mid - i + 1;
        }
    }
    for (; i <= mid; i++, k++) {
        a[k] = s[i];
    }
    for (; j <= r; j++, k++) {
        a[k] = s[j];
    }
    for (int i = l; i <= r; i++) {
        s[i] = a[i];
    }
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