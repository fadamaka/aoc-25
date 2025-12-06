#include <..\utils\aoc.h>

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

vector<string> fixSplit(vector<string> v) {
    vector<string> fixed;
    for (auto&& i : v) {
        if (i != "") {
            fixed.push_back(i);
        }
    }

    return fixed;
}

int main() {
    vector<string> lines = readFileIntoVector("data.txt");
    vector<vector<long long>> numVecs;
    long long result = 0LL;

    vector<int> splitAt;

    for (size_t i = 1; i < lines[lines.size() - 1].length(); i++) {
        if (lines[lines.size() - 1][i] != ' ') {
            splitAt.push_back(i - 1);
        }
    }
    splitAt.push_back(lines[0].size());

    int prev = 0;

    for (auto&& i : splitAt) {
        vector<string> v;
        for (auto&& line : lines) {
            v.push_back(line.substr(prev, i - prev));
        }
        bool mult = v[v.size() - 1][0] == '*';
        long long res = 0;
        if (mult) {
            res = 1;
            for (size_t x = 0; x < v[0].size(); x++) {
                string num = "";
                for (size_t y = 0; y < v.size() - 1; y++) {
                    if (v[y][x] != ' ') {
                        num += v[y][x];
                    }
                }
                // cout << num << '*';
                res *= stoll(num);
            }
        } else {
            for (size_t x = 0; x < v[0].size(); x++) {
                string num = "";
                for (size_t y = 0; y < v.size() - 1; y++) {
                    if (v[y][x] != ' ') {
                        num += v[y][x];
                    }
                }
                // cout << num << '+';
                res += stoll(num);
            }
        }
        prev = i + 1;
        // cout << "=" << res << endl;
        result += res;
    }

    cout << result << endl;
}