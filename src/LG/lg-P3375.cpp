#include <cstring>
#include <iostream>

int nxt[1005];

void init(std::string s);

void kmp(std::string t, std::string p);

int main() {
    std::ios::sync_with_stdio(false);

    std::string t, p;
    std::cin >> t >> p;
    kmp(t, p);
    for (int i = 1; i <= p.length(); i++) {
        std::cout << nxt[i] << ' ';
    }
    std::cout << '\n';

    return 0;
}

void init(std::string s) {
    int i = 0, j;
    nxt[0] = j = -1;
    while (i < s.length()) {
        if (j == -1 or s[i] == s[j]) {
            nxt[++i] = ++j;
        } else {
            j = nxt[j];
        }
    }
}

void kmp(std::string t, std::string p) {
    init(p);
    int i = 0, j = 0;
    while (i < t.length()) {
        if (j == -1 or t[i] == p[j]) {
            i++, j++;
        } else {
            j = nxt[j];
        }
        if (j == p.length()) {
            std::cout << i - p.length() + 1 << '\n';
            j = nxt[j];
        }
    }
}