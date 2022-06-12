#include <bits/stdc++.h>

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    freopen("transfer.in", "r", stdin);
    freopen("transfer.out", "w", stdout);
    std::ios::sync_with_stdio(false);

    int n, res{};
    read(n);
    std::list<std::pair<int, int>> s;
    for (int i = 1; i <= n; i++) {
        int op, c, t;
        read(op, c, t);
        if (op == 0) {
            res += c;
            s.push_back({c, t});
        } else {
            bool flag{};
            while (!s.empty() and t - s.front().second > 45) {
                s.pop_front();
            }
            for (auto it = s.begin(); it != s.end();) {
                if (it->first >= c) {
                    it = s.erase(it);
                    flag = true;
                    break;
                } else {
                    it++;
                }
            }
            if (!flag) {
                res += c;
            }
        }
    }
    std::cout << res << '\n';

    std::cout << std::flush;
    fclose(stdin);
    fclose(stdout);
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

template <typename T>
void read(T& t) {
    t = read<T>();
}

template <typename T, typename... Args>
void read(T& t, Args&... rest) {
    t = read<T>();
    read(rest...);
}