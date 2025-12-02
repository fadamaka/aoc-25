#include <..\utils\aoc.h>

#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<string> lines = readFileIntoVector("data.txt");
    vector<string> ranges = splitByChar(lines[0], ',');

    long long result = 0;
    for (size_t i = 0; i < ranges.size(); i++) {
        vector<string> rangeVector = splitByChar(ranges[i], '-');
        string startStr = rangeVector[0];
        long long startHalf = stoll(startStr.size() > 1 ? startStr.substr(0, startStr.size() / 2) : "1");
        long long start = stoll(rangeVector[0]);
        long long end = stoll(rangeVector[1]);

        long long mul = 1LL;
        long long num = startHalf;
        while (num) {
            num /= 10LL;
            mul *= 10LL;
        }
        long long j = startHalf;
        while (j + j * mul <= end) {
            if (j + j * mul >= start) {
                result += j + j * mul;
            }
            j++;
            mul = 1LL;
            num = j;
            while (num) {
                num /= 10LL;
                mul *= 10LL;
            }
        }
    }

    cout << result << endl;
}
