#include <cstdio>
#include <iostream>
#include <regex>
#include <unordered_map>

std::unordered_map<std::string, int> mp;
std::regex rm(
    R"ccf(^(\d|[1-9]\d|1\d{2}|2[0-4]\d|25[0-5])\.(\d|[1-9]\d|1\d{2}|2[0-4]\d|25[0-5])\.(\d|[1-9]\d|1\d{2}|2[0-4]\d|25[0-5])\.(\d|[1-9]\d|1\d{2}|2[0-4]\d|25[0-5])\:(\d|[1-9]\d{1,3}|[1-5]\d{4}|6[0-4]\d{3}|65[0-4]\d{2}|655[0-2]\d|6553[0-5])$)ccf");

int main() {
    freopen("network.in", "r", stdin);
    freopen("network.out", "w", stdout);
    std::ios::sync_with_stdio(false);

    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::string op, ad;
        std::cin >> op >> ad;
        if (!std::regex_match(ad, rm)) {
            std::cout << "ERR" << '\n';
            continue;
        }
        if (op == "Server") {
            if (mp.find(ad) == mp.end()) {
                mp[ad] = i;
                std::cout << "OK" << '\n';
            } else {
                std::cout << "FAIL" << '\n';
            }
        } else {
            if (mp.find(ad) != mp.end()) {
                std::cout << mp[ad] << '\n';
            } else {
                std::cout << "FAIL" << '\n';
            }
        }
    }

    std::cout << std::flush;
    fclose(stdin);
    fclose(stdout);
    return 0;
}