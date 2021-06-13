#include <cstring>
#include <iostream>

const int MAX_N = 100010;

int tree[MAX_N][15], tot;
bool exi[MAX_N];

bool insert(std::string s);

int main() {
    std::ios::sync_with_stdio(false);

    int T;
    std::cin >> T;
    while (T--) {
        memset(tree, 0, sizeof(tree));
        memset(exi, false, sizeof(exi));
        tot = 1;
        bool flag = false;

        int n;
        std::cin >> n;
        for (int i = 0; i < n; i++) {
            std::string t;
            std::cin >> t;
            if (insert(t)) {
                flag = true;
            }
        }
        if (flag) {
            std::cout << "NO\n";
        } else {
            std::cout << "YES\n";
        }
    }

    return 0;
}

bool insert(std::string s) {
    int len = s.length(), x = 1;
    bool flag = false;
    for (int i = 0; i < len; i++) {
        int ch = s[i] - '0';
        if (!tree[x][ch]) {
            tree[x][ch] = ++tot;
        } else if (i == len - 1) {
            flag = true;
        }
        x = tree[x][ch];
        if (exi[x]) {
            flag = true;
        }
    }
    exi[x] = true;
    return flag;
}