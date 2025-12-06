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
    for (size_t i = 0; i < splitByChar(lines[0], ' ').size(); i++) {
        numVecs.push_back(vector<long long>());
    }

    for (size_t i = 0; i < lines.size(); i++) {
        if (isInt(lines[i][0]) || lines[i][0] == ' ') {
            vector<string> split = fixSplit(splitByChar(lines[i], ' '));

            // vector<long long> nums;
            // transform(split.begin(), split.end(), back_inserter(nums), [](const string& str) { return stoll(str); });

            for (size_t j = 0; j < split.size(); j++) {
                numVecs[j].push_back(stoll(split[j]));
            }
        } else {
            vector<string> split = fixSplit(splitByChar(lines[i], ' '));

            auto mul = [](const long long& a, const long long& b) { return a * b; };
            auto add = [](const long long& a, const long long& b) { return a + b; };
            for (size_t j = 0; j < split.size(); j++) {
                if (split[j] == "+") {
                    result += reduce(numVecs[j].begin(), numVecs[j].end(), 0LL);
                } else {
                    result += reduce(numVecs[j].begin(), numVecs[j].end(), 1LL, mul);
                }
            }
        }
    }

    // auto print = [](const long long& n) { std::cout << n << ' '; };
    // for (auto&& v : numVecs) {
    //     for_each(v.begin(), v.end(), print);
    //     cout << endl;
    // }

    cout << result << endl;
}