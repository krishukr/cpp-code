#include <cstdio>
#include <iostream>

constexpr int MAX_N = 1000050;

int a[MAX_N], b[MAX_N], c[MAX_N];
int ans;

void dfs(int l, int r);

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
    for (int i = 1; i <= n; i++) {
        read(b[i]);
    }
    for (int i = 1; i <= n; i++) {
        c[a[i]]++;
    }

    dfs(1, n);
    std::cout << ans << '\n';

    return 0;
}

void dfs(int l, int r) {
    if (r < l or r - l + 1 <= ans) {
        for (int i = l; i <= r; i++) {
            c[a[i]]--;
            return;
        }
    }
    if (l == r) {
        c[a[l]]--;
        if (b[1] == 1) {
            ans = std::max(ans, 1);
        }
        return;
    }
    int p = l, q = r, t = -1, v = b[r - l + 1];
    while (p <= q) {
        if (c[a[p]] < v) {
            t = p;
            break;
        }
        if (c[a[q]] < v) {
            t = q;
            break;
        }
        p++;
        q--;
    }
    if (t == -1) {
        ans = std::max(ans, r - l + 1);
        for (int i = l; i <= r; i++) {
            c[a[i]]--;
        }
        return;
    }
    if (t <= (l + r) >> 1) {
        for (int i = l; i <= t; i++) {
            c[a[i]]--;
        }
        dfs(t + 1, r);
        for (int i = l; i < t; i++) {
            c[a[i]]++;
        }
        dfs(l, t - 1);
    } else {
        for (int i = t; i <= r; i++) {
            c[a[i]]--;
        }
        dfs(l, t - 1);
        for (int i = t + 1; i <= r; i++) {
            c[a[i]]++;
        }
        dfs(t + 1, r);
    }
}

template <typename T>
T read() {
    T x = 0, f = 1;
    char ch = getchar_unlocked();
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