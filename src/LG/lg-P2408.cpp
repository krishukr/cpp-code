#include <cstdio>
#include <cstring>
#include <iostream>

typedef long long ll;

const int MAX_N = 4000050;

ll dp[MAX_N];

class SAM {
   private:
    const static int CHA_SIZE = 26;
    const static int MAX_N = 4000050;

    int siz;
    int lst;

    struct Node {
        int len;
        int lnk;
        int nxt[CHA_SIZE];
    } node[MAX_N];

   public:
    SAM() {
        node[siz++] = (Node){0, -1};
        lst = 0;
    }

    void insert(const char& c) {
        int crt = siz++;
        node[crt].len = node[lst].len + 1;

        int p = lst;
        while (p != -1 and !node[p].nxt[c]) {
            node[p].nxt[c] = crt;
            p = node[p].lnk;
        }

        if (p == -1) {
            node[crt].lnk = 0;
        } else {
            int q = node[p].nxt[c];
            if (node[p].len + 1 == node[q].len) {
                node[crt].lnk = q;
            } else {
                int cpy = siz++;
                node[cpy] = (Node){node[p].len + 1, node[q].lnk};
                for (int i = 0; i < CHA_SIZE; i++) {
                    node[cpy].nxt[i] = node[q].nxt[i];
                }

                while (p != -1 and node[p].nxt[c] == q) {
                    node[p].nxt[c] = cpy;
                    p = node[p].lnk;
                }
                node[q].lnk = node[crt].lnk = cpy;
            }
        }

        lst = crt;
    }

    ll dfs(int x) {
        if (dp[x]) {
            return dp[x];
        }
        for (int i = 0; i < CHA_SIZE; i++) {
            if (node[x].nxt[i]) {
                dp[x] += dfs(node[x].nxt[i]) + 1;
            }
        }
        return dp[x];
    }
};

int main() {
    std::ios::sync_with_stdio(false);

    SAM* sam = new SAM();

    int n;
    std::string s;
    std::cin >> n >> s;
    for (auto i : s) {
        sam->insert(i - 'a');
    }

    std::cout << sam->dfs(0) << '\n';

    delete sam;
    return 0;
}
