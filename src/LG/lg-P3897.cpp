#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <set>

int main() {
    std::ios::sync_with_stdio(false);

    std::map<std::string, std::set<int>> m;

    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        int x;
        std::cin >> x;
        while (x--) {
            std::string s;
            std::cin >> s;
            m[s].insert(i);
        }
    }

    std::cin >> n;
    while (n--) {
        std::string s;
        std::cin >> s;
        for (auto i : m[s]) {
            std::cout << i << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}