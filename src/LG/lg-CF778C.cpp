#include <cstdio>
#include <iostream>

constexpr int MAX_N = 300050;

int trie[MAX_N << 1][32], sum[MAX_N];
int cnt, n;

int merge(int x, int y);

void dfs(int x, int d);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    read(n);
    for (int i = 1; i < n; i++) {
        int x, y;
        read(x, y);
        char ch = getchar();
        while (!islower(ch)) {
            ch = getchar();
        }
        trie[x][ch - 'a'] = y;
    }

    dfs(1, 1);
    int mx{}, ans{};
    for (int i = 1; i <= n; i++) {
        if (mx < sum[i]) {
            mx = sum[i];
            ans = i;
        }
    }

    std::cout << n - mx << '\n' << ans << '\n';

    return 0;
}

int merge(int x, int y) {
    if (!x or !y) {
        return x + y;
    }
    int c = ++cnt;
    for (int i = 0; i < 26; i++) {
        trie[c][i] = merge(trie[x][i], trie[y][i]);
    }
    return c;
}

void dfs(int x, int d) {
    int dc = (cnt = n + 1);
    for (int i = 0; i < 26; i++) {
        if (trie[x][i]) {
            dc = merge(dc, trie[x][i]);
        }
    }
    sum[d] += cnt - n - 1;
    for (int i = 0; i < 26; i++) {
        if (trie[x][i]) {
            dfs(trie[x][i], d + 1);
        }
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