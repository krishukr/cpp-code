#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <list>
#include <stack>

void out(std::string s);

int pri(char x);

int num(int a, int b, char op);

std::string trans(std::string s);

void calc(std::string s);

int main() {
    std::ios::sync_with_stdio(false);

    std::string s;
    std::cin >> s;
    calc(trans(s));

    return 0;
}

void out(std::string s) {
    for (auto i : s) {
        std::cout << i << ' ';
    }
    std::cout << '\n';
}

int pri(char x) {
    switch (x) {
        case '(':
        case ')':
            return 0;
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return -1;
    }
}

std::string trans(std::string s) {
    std::string res{};
    std::stack<char> stk;

    for (auto i : s) {
        if (isdigit(i)) {
            res.push_back(i);
        } else if (i == '(') {
            stk.push(i);
        } else if (i == ')') {
            while (!stk.empty() and stk.top() != '(') {
                res.push_back(stk.top());
                stk.pop();
            }
            stk.pop();
        } else {
            while (!stk.empty() and pri(stk.top()) >= pri(i)) {
                res.push_back(stk.top());
                stk.pop();
            }
            stk.push(i);
        }
    }

    while (!stk.empty()) {
        res.push_back(stk.top());
        stk.pop();
    }
    return res;
}

int num(int a, int b, char op) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        case '^':
            return std::pow(a, b);
        default:
            return -1;
    }
}

void calc(std::string s) {
    out(s);
    std::list<int> stk;

    for (auto it = s.begin(); it != s.end(); it++) {
        auto i = *it;
        if (isdigit(i)) {
            stk.push_back(i - 48);
        } else {
            int b = stk.back();
            stk.pop_back();
            int a = stk.back();
            stk.pop_back();
            stk.push_back(num(a, b, i));

            for (auto j : stk) {
                std::cout << j << ' ';
            }
            for (auto jt = it + 1; jt != s.end(); jt++) {
                auto j = *jt;
                std::cout << j << ' ';
            }
            std::cout << '\n';
        }
    }
}
