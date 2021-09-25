#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <set>
#include <vector>

int n, m, p, q;
std::set<std::string> rq;
std::string ans;

void dfs(int dep, std::string s);

std::string rev(std::string s);

std::map<std::string, int> mp;

template <typename T>
T read();

int main() {
    freopen("answer.in", "r", stdin);
    freopen("answer.out", "w", stdout);

    n = read<int>(), m = read<int>(), p = read<int>(), q = read<int>();

    for (int i = 1; i <= n; i++) {
        std::string s;
        std::cin >> s;
        mp[s]++;
        rq.insert(s);
    }

    if (!p and !q) {
        for (int i = 0; i < m; i++) {
            ans += 'a';
        }
        dfs(0, "");
        if (ans[0] == 'a') {
            std::cout << "-1\n";
        } else {
            std::cout << ans << '\n';
        }
        return 0;
    }

    for (auto i : rq) {
        if (mp[i] == p and mp[rev(i)] == q) {
            std::cout << i << '\n';
            return 0;
        }
        if (mp[i] == q and mp[rev(i)] == p) {
            std::cout << rev(i) << '\n';
            return 0;
        }
    }

    std::cout << "-1\n";
    fclose(stdin);
    fclose(stdout);
    return 0;
}

void dfs(int dep, std::string s) {
    if (dep == m) {
        if (mp[s] == 0 and mp[rev(s)] == 0 and ans > s) {
            ans = s;
        }
        return;
    }
    dfs(dep + 1, s + 'Y');
    dfs(dep + 1, s + 'N');
}

std::string rev(std::string s) {
    std::string res;
    for (auto i : s) {
        if (i == 'Y') {
            res.push_back('N');
        } else {
            res.push_back('Y');
        }
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