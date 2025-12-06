#include <..\utils\aoc.h>

#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<string> lines = readFileIntoVector("data.txt");
    vector<string> freshRanges;
    long long i = 0;
    long long result = 0;
    while (lines[i] != "") {
        freshRanges.push_back(lines[i++]);
    }
    for (long long j = i + 1; j < lines.size(); j++) {
        for (auto&& str : freshRanges) {
            vector<string> split = splitByChar(str, '-');
            long long start = stoll(split[0]);
            long long end = stoll(split[1]);

            long long sub = stoll(lines[j]);

            if (start <= sub && sub <= end) {
                result++;
                break;
            }
        }
    }
    cout << result << endl;
}