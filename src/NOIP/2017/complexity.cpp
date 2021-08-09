#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <stack>

int lp, ans, max, k, c;
bool flag1, flag2;
bool vis[500];

std::stack<std::pair<char, int>> l;

template <typename T>
T read();

int work(std::string s);

int main() {
    freopen("complexity.in", "r", stdin);
    freopen("complexity.out", "w", stdout);

    int T = read<int>();
    while (T--) {
        lp = ans = max = k = c = flag1 = flag2 = 0;
        memset(vis, 0, sizeof(vis));
        while (!l.empty()) {
            l.pop();
        }

        int cnt = read<int>(), com = 0;
        std::string c;
        std::cin >> c;

        if (c[2] == '1') {
            flag2 = true;
        } else {
            com = work(c);
        }

        for (int i = 1; i <= cnt; i++) {
            char o;
            std::cin >> o;
            if (o == 'F') {
                char a;
                std::string b, c;

                std::cin >> a >> b >> c;
                k++;
                int x = work(b), y = work(c);

                if (vis[a]) {
                    flag1 = true;
                } else {
                    vis[a] = true;
                }

                if (x > y) {
                    l.push(std::make_pair(a, 1));
                    lp++;
                } else {
                    l.push(std::make_pair(a, 0));
                }

                if (b != "n" and c == "n" and !lp) {
                    ans++;
                }
            } else {
                k--;
                if (!lp and ans) {
                    ans--;
                }

                if (l.empty()) {
                    flag1 = true;
                } else {
                    if (l.top().second) {
                        lp--;
                    }
                    vis[l.top().first] = false;
                    l.pop();
                }
            }
            max = std::max(max, ans);

            if (k == -1) {
                flag1 = true;
            }
            if (k == 0) {
                memset(vis, 0, sizeof(vis));
            }
        }
        if (k) {
            flag1 = true;
        }

        if (flag1) {
            std::cout << "ERR\n";
        } else {
            if ((flag2 and !max) or com == max) {
                std::cout << "Yes\n";
            } else {
                std::cout << "No\n";
            }
        }
    }

    fclose(stdin);
    fclose(stdout);
    return 0;
}

int work(std::string s) {
    if (s == "n") {
        return INT_MAX;
    } else {
        int res = 0;
        for (auto i : s) {
            if (isdigit(i)) {
                res = res * 10 + i - 48;
            }
        }
        return res;
    }
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