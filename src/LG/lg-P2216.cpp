#include <climits>
#include <cstdio>
#include <iostream>
#include <queue>

constexpr int MAX_N = 1050;

int mp[MAX_N][MAX_N];
int mx[MAX_N][MAX_N], nx[MAX_N][MAX_N];
int my[MAX_N][MAX_N], ny[MAX_N][MAX_N];

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    int a, b, n;
    read(a, b, n);
    for (int i = 1; i <= a; i++) {
        for (int j = 1; j <= b; j++) {
            read(mp[i][j]);
        }
    }

    for (int i = 1; i <= a; i++) {
        std::deque<int> q1{1}, q2{1};
        for (int j = 2; j <= b; j++) {
            while (!q1.empty() and mp[i][q1.back()] <= mp[i][j]) {
                q1.pop_back();
            }
            while (!q2.empty() and mp[i][q2.back()] >= mp[i][j]) {
                q2.pop_back();
            }
            q1.push_back(j);
            q2.push_back(j);

            while (n <= j - q1.front()) {
                q1.pop_front();
            }
            while (n <= j - q2.front()) {
                q2.pop_front();
            }

            if (n <= j) {
                mx[i][j - n + 1] = mp[i][q1.front()];
                nx[i][j - n + 1] = mp[i][q2.front()];
            }
        }
    }

    for (int i = 1; i <= b - n + 1; i++) {
        std::deque<int> q1{1}, q2{1};
        for (int j = 2; j <= a; j++) {
            while (!q1.empty() and mx[q1.back()][i] <= mx[j][i]) {
                q1.pop_back();
            }
            while (!q2.empty() and nx[q2.back()][i] >= nx[j][i]) {
                q2.pop_back();
            }
            q1.push_back(j);
            q2.push_back(j);

            while (n <= j - q1.front()) {
                q1.pop_front();
            }
            while (n <= j - q2.front()) {
                q2.pop_front();
            }

            if (n <= j) {
                my[j - n + 1][i] = mx[q1.front()][i];
                ny[j - n + 1][i] = nx[q2.front()][i];
            }
        }
    }

    int r{INT_MAX};
    for (int i = 1; i <= a - n + 1; i++) {
        for (int j = 1; j <= b - n + 1; j++) {
            r = std::min(r, my[i][j] - ny[i][j]);
        }
    }
    std::cout << r << '\n';

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