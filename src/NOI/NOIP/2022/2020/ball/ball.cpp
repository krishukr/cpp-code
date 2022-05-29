#include <cstdio>
#include <iostream>
#include <vector>

constexpr int MAX_N = 55;
constexpr int MAX_M = 405;

int top[MAX_N];
int a[MAX_N][MAX_M], cnt[MAX_N][MAX_M];
int n, m;
std::vector<std::pair<int, int>> ans;

void move(int x, int y);

void dfs(int x);

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    freopen("ball.in", "r", stdin);
    freopen("ball.out", "w", stdout);
    std::ios::sync_with_stdio(false);

    read(n, m);
    for (int i = 1; i <= n; i++) {
        top[i] = m;
        for (int j = 1; j <= m; j++) {
            read(a[i][j]);
            cnt[i][a[i][j]]++;
        }
    }

    dfs(n);
    std::cout << ans.size() << '\n';
    for (const auto& i : ans) {
        std::cout << i.first << ' ' << i.second << '\n';
    }

    std::cout << std::flush;
    fclose(stdin);
    fclose(stdout);
    return 0;
}

void move(int x, int y) {
    ans.push_back({x, y});
    cnt[x][a[x][top[x]]]--;
    cnt[y][a[x][top[x]]]++;
    a[y][++top[y]] = a[x][top[x]--];
}

void dfs(int x) {
    if (x == 1) {
        return;
    }
    for (int i = 1; i < x; i++) {
        const auto c = cnt[i][x];
        for (int j = c; j > 0; j--) {
            move(x, x + 1);
        }
        for (int j = m; j > 0; j--) {
            if (a[i][j] == x) {
                move(i, x);
            } else {
                move(i, x + 1);
            }
        }
        for (int j = m - c; j > 0; j--) {
            move(x + 1, i);
        }
        for (int j = c; j > 0; j--) {
            move(x, i);
        }
        for (int j = c; j > 0; j--) {
            move(x + 1, x);
        }
    }
    for (int i = 1; i < x; i++) {
        while (a[i][top[i]] == x) {
            move(i, x + 1);
        }
    }

    for (int i = top[x], j = 1; i > 0; i--) {
        if (a[x][i] == x) {
            move(x, x + 1);
        } else {
            while (top[j] >= m) {
                j++;
            }
            move(x, j);
        }
    }

    dfs(x - 1);
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