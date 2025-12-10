#include <..\utils\aoc.h>
#include <math.h>

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

typedef long long i64;

i64 strToDecimal(string strEnd) {
    i64 numEnd = 0;
    for (int i = 0; i < strEnd.size(); i++) {
        if (strEnd[i] == '#') {
            numEnd += pow(2, i);
        }
    }
    return numEnd;
}
i64 listToDecimal(string list, size_t bitCount) {
    // cout << list << endl;
    vector<string> split = splitByChar(list.substr(1, list.size() - 2), ',');
    i64 num = 0;
    for (auto&& i : split) {
        if (bitCount > stoll(i)) {
            num += pow(2, stoll(i));
        } else {
            break;
        }
    }
    return num;
}

vector<vector<i64>> comb(int N, int K) {
    vector<vector<i64>> combinations;
    std::string bitmask(K, 1);  // K leading 1's
    bitmask.resize(N, 0);       // N-K trailing 0's

    // print integers and permute bitmask
    do {
        vector<i64> combination;
        for (i64 i = 0; i < N; ++i)  // [0..N-1] integers
        {
            if (bitmask[i]) {
                combination.push_back(i);
            }
        }
        if (combination.size() > 0) {
            combinations.push_back(combination);
        }
    } while (std::prev_permutation(bitmask.begin(), bitmask.end()));
    return combinations;
}

int main() {
    vector<string> lines = readFileIntoVector("data.txt");
    i64 result = 0;
    for (string str : lines) {
        // cout << str << endl;
        vector<string> split = splitByChar(str, ' ');
        // cout << split[0].substr(1, split[0].size() - 2) << endl;
        string strEnd = split[0].substr(1, split[0].size() - 2);
        size_t bitCount = strEnd.size();
        i64 numEnd = strToDecimal(strEnd);
        // cout << numEnd << endl;
        vector<i64> buttons;
        for (size_t i = 1; i < split.size() - 1; i++) {
            buttons.push_back(listToDecimal(split[i], bitCount));
            // cout << split[i] << " " << listToDecimal(split[i], bitCount) << endl;
        }
        size_t res = 0;
        bool foundB = false;
        for (size_t i = 1; i < buttons.size() + 1; i++) {
            vector<vector<i64>> combinations = comb(buttons.size(), i);
            for (vector<i64> comb : combinations) {
                vector<i64> comb2;
                for (auto&& k : comb) {
                    comb2.push_back(buttons[k]);
                }

                if (numEnd == reduce(comb2.begin(), comb2.end(), 0LL, [](const long long& a, const long long& b) { return a ^ b; })) {
                    res = i;
                    // cout << i << endl;
                    foundB = true;
                    break;
                }
            }
            if (foundB) {
                result += res;
                break;
            }
        }
    }
    cout << result << endl;
}