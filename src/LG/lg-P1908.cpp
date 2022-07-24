#include <cstdio>
#include <iostream>

constexpr int MAX_N = 500050;

int a[MAX_N], s[MAX_N];
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

    int n;
    read(n);
    for (int i = 1; i <= n; i++) {
        read(a[i]);
    }
    merge_sort(1, n);
    std::cout << ans << '\n';

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
        if (a[i] <= a[j]) {
            s[k] = a[i++];
        } else {
            s[k] = a[j++];
            ans += mid - i + 1;
        }
    }
    for (; i <= mid; i++, k++) {
        s[k] = a[i];
    }
    for (; j <= r; j++, k++) {
        s[k] = a[j];
    }
    for (int i = l; i <= r; i++) {
        a[i] = s[i];
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

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}