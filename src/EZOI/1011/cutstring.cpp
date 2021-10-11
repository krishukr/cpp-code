#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <vector>

std::map<std::string, std::vector<int>> m;

std::vector<int> init(std::string s);

std::vector<int> kmp(std::string t, std::string p);

int main() {
    freopen("cutstring.in", "r", stdin);
    freopen("cutstring.out", "w", stdout);

    std::string s, t;
    std::cin >> s >> t;
    if (s == t) {
        std::cout << 0 << '\n';
        return 0;
    } else if (s.size() == t.size()) {
        std::cout << -1 << '\n';
        return 0;
    }

    if (!(kmp(s, t).size())) {
        std::cout << -1 << '\n';
        return 0;
    }

    for (int i = 1; i <= s.size(); i++) {
        if (kmp(s, s.substr(0, i)).size() and
            kmp(s, s.substr(s.size() - i, i)).size()) {
            continue;
        }
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}

std::vector<int> init(std::string s) {
    if (m[s].size()) {
        return m[s];
    }
    std::vector<int> res;
    res.resize(s.length());
    int i = 0, j;
    res[0] = j = -1;
    while (i < s.length()) {
        if (j == -1 or s[i] == s[j]) {
            res[++i] = ++j;
        } else {
            j = res[j];
        }
    }
    m[s] = res;
    return res;
}

std::vector<int> kmp(std::string t, std::string p) {
    std::vector<int> res, nxt = init(p);
    int i = 0, j = 0;
    while (i < t.length()) {
        if (j == -1 or t[i] == p[j]) {
            i++, j++;
        } else {
            j = nxt[j];
        }
        if (j == p.length()) {
            j = nxt[j];
            res.push_back(i - p.length());
        }
    }
    return res;
}