#include <cstdio>
#include <iostream>
#include <queue>

template <typename T, template <typename> class C>
using pq = std::priority_queue<T, std::vector<T>, C<T>>;

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    pq<int, std::less> qg;
    pq<int, std::greater> ql;

    int n;
    read(n);
    for (int i = 1; i <= n; i++) {
        int x;
        read(x);
        if (i & 1) {
            qg.push(x);
        } else {
            ql.push(x);
        }

        if (!qg.empty() and !ql.empty() and ql.top() < qg.top()) {
            const auto a = qg.top(), b = ql.top();
            qg.pop();
            ql.pop();
            ql.push(a);
            qg.push(b);
        }

        if (i & 1) {
            std::cout << qg.top() << '\n';
        }
    }

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