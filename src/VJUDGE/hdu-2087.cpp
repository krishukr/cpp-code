#include <cstring>
#include <iostream>

int nxt[1005];

void init(std::string s);

int kmp(std::string t, std::string p);

int main() {
    std::ios::sync_with_stdio(false);

    std::string t, p;
    while (std::cin >> t) {
        if (t[0] == '#') {
            break;
        }
        std::cin >> p;
        std::cout << kmp(t, p) << '\n';
    }

    return 0;
}

void init(std::string s) {
    memset(nxt, 0, sizeof(nxt));
    for (int i = 1; i < s.length(); i++) {
        int j = nxt[i - 1];
        while (j > 0 and s[i] != s[j]) {
            j = nxt[j - 1];
        }
        if (s[i] == s[j]) {
            j++;
        }
        nxt[i] = j;
    }
}

int kmp(std::string t, std::string p) {
    init(p);
    int res = 0, i = 0, j = 0;
    while (i < t.length()) {
        if (t[i] == p[j]) {
            i++, j++;
        } else {
            if (j == 0) {
                i++;
            } else {
                j = nxt[i - 1];
            }
        }
        if (j == p.length()) {
            res++;
            j = 0;
        }
    }
    return res;
}