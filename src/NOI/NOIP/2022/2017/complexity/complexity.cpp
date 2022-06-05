#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <memory>
#include <stack>

class Solution {
   private:
    std::stack<std::pair<char, bool>> loop_stack;
    bool vis[32];

    int string2Int(const std::string& s);

   public:
    Solution() = default;
    ~Solution() = default;

    void solve();
};

int main() {
    freopen("complexity.in", "r", stdin);
    freopen("complexity.out", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;
    while (T--) {
        auto solution = std::make_unique<Solution>();
        solution->solve();
    }

    std::cout << std::flush;
    fclose(stdin);
    fclose(stdout);
    return 0;
}

int Solution::string2Int(const std::string& s) {
    if (s == "n") {
        return INT_MAX;
    } else {
        int r{};
        for (const auto& i : s) {
            if (isdigit(i)) {
                r = r * 10 + i - 48;
            }
        }
        return r;
    }
}

void Solution::solve() {
    int line_count;
    std::cin >> line_count;

    int expected_complexity;
    bool bExpected_complexity_constant{};
    {
        std::string s;
        std::cin >> s;
        if (s[2] == '1') {
            bExpected_complexity_constant = true;
        } else {
            expected_complexity = string2Int(s);
        }
    }

    int loop_depth{}, unreachable_loop_count{}, max_complexity{},
        current_complexity{};
    bool bCompile_error{};
    while (line_count--) {
        char op;
        std::cin >> op;
        if (op == 'F') {
            loop_depth++;
            char qi;
            std::string qx, qy;
            std::cin >> qi >> qx >> qy;
            int iqx = string2Int(qx), iqy = string2Int(qy);

            if (vis[qi - 'a']) {
                bCompile_error = true;
            } else {
                vis[qi - 'a'] = true;
            }

            if (iqx > iqy) {
                unreachable_loop_count++;
                loop_stack.push({qi, true});
            } else {
                loop_stack.push({qi, false});
            }

            if (qx != "n" and qy == "n" and !unreachable_loop_count) {
                current_complexity++;
            }
        } else if (op == 'E') {
            loop_depth--;
            if (!unreachable_loop_count and current_complexity > 0) {
                current_complexity--;
            }

            if (loop_stack.empty()) {
                bCompile_error = true;
            } else {
                if (loop_stack.top().second) {
                    unreachable_loop_count--;
                }
                vis[loop_stack.top().first - 'a'] = false;
                loop_stack.pop();
            }
        }
        max_complexity = std::max(max_complexity, current_complexity);

        if (loop_depth < 0) {
            bCompile_error = true;
        }
    }
    if (loop_depth > 0) {
        bCompile_error = true;
    }
    if (bCompile_error) {
        std::cout << "ERR" << '\n';
    } else {
        std::cout << ((bExpected_complexity_constant and max_complexity == 0) or
                              expected_complexity == max_complexity
                          ? "Yes"
                          : "No")
                  << '\n';
    }
}