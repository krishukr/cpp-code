#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

const int MAX_N = 4100000;

int s[MAX_N], vis[MAX_N];

template <typename T>
T read();

int main() {
    std::ios::sync_with_stdio(false);

    int n = read<int>();
    int t = n * (n + 1) / 2;

    for (int i = 1; i <= t; i++) {
        s[i] = read<int>();
    }
    std::sort(s + 1, s + t + 1);

    int lst = 0;
    std::vector<int> ans;
    for (int i = 1; i <= t; i++) {
        if (!vis[s[i]]) {
            lst += s[i];
            vis[lst] = true;
            ans.push_back(s[i]);
            if (ans.size() == n) {
                break;
            }
        }
    }

    std::for_each(ans.begin(), ans.end(),
                  [](const int &i) -> void { std::cout << i << ' '; });

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