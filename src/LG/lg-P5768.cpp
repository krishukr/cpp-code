#include <cstdio>
#include <iostream>
#include <stack>

constexpr int MAX_N = 32000050;

struct Node {
    int w;
    int son[2];
} trie[MAX_N];

int stk[MAX_N];
int cnt = 1, crt, skc;

void insert(const unsigned int& a, const int& m);

int query(const unsigned int& a, const int& k);

unsigned int readIP();

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int m;
    read(m);
    while (m--) {
        char op = getchar();
        while (op != 'A' and op != 'Q') {
            op = getchar();
        }

        if (op == 'A') {
            const unsigned int a = readIP();
            insert(a, read<int>());
        } else if (op == 'Q') {
            const unsigned int a = readIP();
            int l, r;
            read(l, r);
            std::cout << query(a, r) - query(a, l - 1) << '\n';
        }
    }

    return 0;
}

void insert(const unsigned int& a, const int& m) {
    int c = 1;
    for (int i = 31; 32 - i <= m; i--) {
        const int x = (a >> i) & 1;
        c = (trie[c].son[x] ? trie[c].son[x] : (trie[c].son[x] = ++cnt));
    }
    trie[c].w = ++crt;
}

int query(const unsigned int& a, const int& k) {
    skc = 0;
    int c = 1;
    for (int i = 31;; i--) {
        if (trie[c].w and trie[c].w <= k) {
            while (skc and trie[c].w < stk[skc - 1]) {
                skc--;
            }
            stk[skc++] = trie[c].w;
        }

        const int x = (a >> i) & 1;
        if (trie[c].son[x]) {
            c = trie[c].son[x];
        } else {
            break;
        }
    }
    std::fill_n(stk, skc + 1, 0);
    return skc;
}

unsigned int readIP() {
    unsigned int res{};
    for (int i = 1; i <= 4; i++) {
        res = (res << 8) + read<int>();
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

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}