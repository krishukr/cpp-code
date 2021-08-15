#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>

const int MAX_N = 101;

bool vis[MAX_N];
std::string e[MAX_N];
int n;

std::set<std::string> s;

void dfs(int x, std::string c);

int main() {
    freopen("csm.in", "r", stdin);
    freopen("csm.out", "w", stdout);

    std::cin >> n;

    if (n) {
        for (int i = 0; i < n; i++) {
            std::cin >> e[i];
        }

        dfs(n, "");
        std::cout << s.size() << '\n';
    } else {
        std::cout << "0\n";
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}

void dfs(int x, std::string c) {
    if (!x) {
        if (c[0] != '0') {
            s.insert(c);
        }
    } else {
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                vis[i] = true;
                dfs(x - 1, c + e[i]);
                vis[i] = false;
            }
        }
    }
}
