#include <cstdio>
#include <cstring>
#include <functional>
#include <iostream>
#include <stack>

template <typename T>
T read();

int main() {
    freopen("logic.in", "r", stdin);
    freopen("logic.out", "w", stdout);

    int T = read<int>();
    while (T--) {
        int n = read<int>();
        int cnt = n;
        std::string s;
        std::getline(std::cin, s);
        std::getline(std::cin, s);
        auto* var = new int[n + n + 10]{};
        auto* son = new int[n + 10][2]{{}, {}};

        for (int i = 1; i <= n; i++) {
            var[i] = read<int>();
        }

        std::stack<int> stk;

        for (int i = 0; i < s.size(); i += 2) {
            if (s[i] == 'x') {
                int idx = 0;
                i++;
                while (s[i] != ' ') {
                    idx = idx * 10 + s[i] - 48;
                    i++;
                }
                i--;
                stk.push(idx);
            } else if (s[i] == '&') {
                int a = stk.top();
                stk.pop();
                int b = stk.top();
                stk.pop();
                stk.push(++cnt);
                var[cnt] = 2;
                son[cnt][0] = a;
                son[cnt][1] = b;
            } else if (s[i] == '|') {
                int a = stk.top();
                stk.pop();
                int b = stk.top();
                stk.pop();
                stk.push(++cnt);
                var[cnt] = 3;
                son[cnt][0] = a;
                son[cnt][1] = b;
            }
        }
    }

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