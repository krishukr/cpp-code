#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>

std::queue<std::pair<std::string, int>> q;
std::map<std::string, bool> hash;
std::pair<std::string, std::string> rule[10];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int cnt = 1;
    std::string u, v;
    std::cin >> u >> v;

    while (std::cin >> rule[cnt].first >> rule[cnt].second) {
        cnt++;
    }

    q.push(std::make_pair(u, 0));
    while (!q.empty()) {
        auto p = q.front();

        if (p.second > 10) {
            std::cout << "NO ANSWER!\n";
            return 0;
        }
        if (p.first == v) {
            std::cout << p.second << '\n';
            return 0;
        }

        for (int i = 1; i < cnt; i++) {
            int pp = 0;
            while (p.first.find(rule[i].first, pp) != p.first.npos) {
                auto w = p.first;
                auto np = p.first.find(rule[i].first, pp);

                w.replace(np, rule[i].first.size(), rule[i].second);
                if (!hash[w]) {
                    q.push(std::make_pair(w, p.second + 1));
                    hash[w] = true;
                }
                pp = np + rule[i].first.size();
            }
        }
        q.pop();
    }
    std::cout << "NO ANSWER!\n";

    return 0;
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