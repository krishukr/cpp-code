#include <cstring>
#include <iostream>
#include <queue>

const int MAX_N = 1000010;

int tree[MAX_N][27], exi[MAX_N], nxt[MAX_N];
int tot;

void build();

void insert(std::string s);

int query(std::string s);

int main() {
    std::ios::sync_with_stdio(false);

    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::string s;
        std::cin >> s;
        insert(s);
    }
    build();
    std::string s;
    std::cin >> s;
    std::cout << query(s) << '\n';

    return 0;
}

void build() {
    std::queue<int> q;
    for (int i = 0; i < 26; i++) {
        if (tree[0][i]) {
            q.push(tree[0][i]);
        }
    }
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (int i = 0; i < 26; i++) {
            if (!tree[x][i]) {
                tree[x][i] = tree[nxt[x]][i];
            } else {
                q.push(tree[x][i]);
                nxt[tree[x][i]] = tree[nxt[x]][i];
            }
        }
    }
}

void insert(std::string s) {
    int x = 0;
    for (int i = 0; s[i]; i++) {
        int ch = s[i] - 'a';
        if (!tree[x][ch]) {
            tree[x][ch] = ++tot;
        }
        x = tree[x][ch];
    }
    exi[x]++;
}

int query(std::string s) {
    int x = 0, res = 0;
    for (int i = 0; s[i]; i++) {
        int ch = s[i] - 'a';
        x = tree[x][ch];
        for (int j = x; j and exi[j] != -1; j = nxt[j]) {
            res += exi[j];
            exi[j] = -1;
        }
    }
    return res;
}
