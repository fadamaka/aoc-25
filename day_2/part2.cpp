#include <..\utils\aoc.h>

#include <cmath>
#include <iostream>
#include <numeric>
#include <set>
#include <string>
#include <vector>

using namespace std;

long long countDigits(long long inputNum);

int main() {
    vector<string> lines = readFileIntoVector("data.txt");
    vector<string> ranges = splitByChar(lines[0], ',');
    long long result = 0;
    set<long long> resSet;
    for (size_t i = 0; i < ranges.size(); i++) {
        vector<string> rangeVector = splitByChar(ranges[i], '-');
        string startStr = rangeVector[0];
        long long start = stoll(rangeVector[0]);
        long long end = stoll(rangeVector[1]);

        long long startDigits = countDigits(start);
        long long endDigits = countDigits(end);

        long long num = 1LL;

        while (countDigits(num) <= endDigits / 2) {
            long long res = num;
            while (res < end) {
                res = num + (res * pow(10, countDigits(num)));
                if (res >= start && res <= end) {
                    resSet.insert(res);
                }
            }
            num++;
        }
    }
    for (set<long long>::iterator it = resSet.begin(); it != resSet.end(); ++it) {
        result += *it;
    }
    cout << result << endl;
}

long long countDigits(long long inputNum) {
    long long num = inputNum;
    long long digits = 0;
    while (num) {
        num /= 10LL;
        digits++;
    }
    return digits;
}
