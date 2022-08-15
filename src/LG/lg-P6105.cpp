#include <cstdio>
#include <iostream>
#include <set>

std::multiset<int> a, b;
int n, c;

int get(int x, int k);

void in(int x);

void rm(int x);

int qry();

template <typename T>
T read();

template <typename T>
void read(T& t);

template <typename T, typename... Args>
void read(T& t, Args&... rest);

int main() {
    std::ios::sync_with_stdio(false);

    read(n, c);
    int la{};
    while (n--) {
        int op, x;
        read(op, x);
        x ^= la;

        if (op == 1) {
            in(x % c);
        } else if (op == 2) {
            rm(x % c);
        }
        if (a.size() < 2) {
            std::cout << "EE\n";
            la = 0;
        } else {
            la = qry();
            std::cout << la << '\n';
        }
    }

    return 0;
}

int get(int x, int k) {
    if (x == -114514) {
        return -114514;
    }
    auto it = a.upper_bound(c - x - 1);
    if (it == a.begin()) {
        return -114514;
    }
    it--;
    if (*it == x and a.count(x) == 1 and k == 1) {
        if (it == a.begin()) {
            return -114514;
        } else {
            it--;
        }
    }
    return *it;
}

void in(int x) {
    if (a.size() == 0) {
        a.insert(x);
        return;
    }
    const auto y = get(x, 0);
    const auto z = get(y, 1);
    const auto i = get(z, 1);
    if (y != -114514 and z < x) {
        if (z != -114514 and y == i) {
            b.erase(b.find(y + z));
        }
        b.insert(x + y);
    }
    a.insert(x);
}

void rm(int x) {
    a.erase(a.find(x));
    if (a.empty()) {
        return;
    }
    const auto y = get(x, 0);
    const auto z = get(y, 1);
    const auto i = get(z, 1);
    if (y != -114514 and z < x) {
        if (z != -114514 and y == i) {
            b.insert(y + z);
        }
        b.erase(b.find(x + y));
    }
}

int qry() {
    auto it = a.end();
    it--;
    return std::max(((*it) + (*(--it))) % c, (b.empty() ? 0 : *(--(b.end()))));
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