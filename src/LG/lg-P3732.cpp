#include <cstdio>
#include <iostream>

constexpr int MAX_N = 100050;
constexpr int MAX_L = 37;

char s[MAX_N];
int n, q;

struct Node {
    int w;
    int son[2];
} trie[MAX_N * MAX_L];

int ans[MAX_N][MAX_L];

int cnt = 1;

void insert(int l);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    read(n, q);
    scanf("%s", s + 1);

    for (int i = 1; i <= n; i++) {
        insert(i);
    }
    for (int i = 2; i <= n; i++) {
        for (int j = 1; j < MAX_L; j++) {
            ans[i][j] = std::max(ans[i][j], ans[i - 1][j]);
        }
    }

    while (q--) {
        int l, r, res{};
        read(l, r);
        for (int i = MAX_L - 1; i > 0; i--) {
            if (l > r) {
                break;
            }
            if (l <= ans[r][i]) {
                res += (ans[r][i] - l + 1) * i;
                l = ans[r][i] + 1;
            }
        }
        std::cout << res << '\n';
    }

    return 0;
}

void insert(int l) {
    int c = 1;
    for (int i = l; i < l + MAX_L - 1; i++) {
        if (i > n) {
            break;
        }
        const int x = (s[i] == '1');
        c = (trie[c].son[x] ? trie[c].son[x] : (trie[c].son[x] = ++cnt));
        ans[l][i - l + 1] = trie[c].w;
        trie[c].w = l;
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