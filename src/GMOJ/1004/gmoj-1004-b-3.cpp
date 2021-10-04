#include <cstring>
#include <iostream>

const int MAX_N = 1000050;

int nxt[MAX_N], ss[MAX_N], tt[MAX_N], pre[MAX_N];
int ans, n, m;

inline bool cmp(int a, int b, int k);

void init(int* s);

void kmp(int* t, int* p);

template <typename T>
T read();

int main() {
    // std::ios::sync_with_stdio(false);

    int t = read<int>();
    while (t--) {
        memset(nxt, 0, sizeof(nxt));
        memset(ss, 0, sizeof(ss));
        memset(tt, 0, sizeof(tt));
        ans = 0;

        std::string s, t;
        std::cin >> s >> t;
        n = s.size(), m = t.size();

        memset(pre, 0, sizeof(pre));
        for (int it = 0; it < s.size(); it++) {
            auto i = s[it];
            if (i - 'a' + 1 > 0) {
                if (pre[i - 'a' + 1]) {
                    ss[it] = it - pre[i - 'a' + 1] + 1;
                } else {
                    ss[it] = 0;
                }
                pre[i - 'a' + 1] = it + 1;
            } else {
                ss[it] = -(i - 'A' + 1);
            }
        }

        memset(pre, 0, sizeof(pre));
        for (int it = 0; it < t.size(); it++) {
            auto i = t[it];
            if (i - 'a' + 1 > 0) {
                if (pre[i - 'a' + 1]) {
                    tt[it] = it - pre[i - 'a' + 1] + 1;
                } else {
                    tt[it] = 0;
                }
                pre[i - 'a' + 1] = it + 1;
            } else {
                tt[it] = -(i - 'A' + 1);
            }
        }

        kmp(ss, tt);
        std::cout << ans << '\n';
    }

    return 0;
}

inline bool cmp(int a, int b, int k) {
    if (a < 0 or b < 0) {
        return a == b;
    } else {
        return a == b or (!b and a > k);
    }
}

void init(int* s) {
    int i = 0, j;
    nxt[0] = j = -1;
    while (i < m) {
        // if (j == -1 or s[i] == s[j]) {
        if (j == -1 or cmp(s[i], s[j], j)) {
            nxt[++i] = ++j;
        } else {
            j = nxt[j];
        }
    }
}

void kmp(int* t, int* p) {
    init(p);
    int i = 0, j = 0;
    while (i < n) {
        // if (j == -1 or t[i] == p[j]) {
        if (j == -1 or cmp(t[i], p[j], j)) {
            i++, j++;
        } else {
            j = nxt[j];
        }
        if (j == m) {
            // std::cout << i - p.length() + 1 << '\n';
            ans++;
            j = nxt[j];
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