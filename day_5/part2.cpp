#include <..\utils\aoc.h>

#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

bool overlaps(pair<long long, long long> one, pair<long long, long long> two) {
    long long localStart = max(one.first, two.first);
    long long localEnd = min(one.second, two.second);
    return 0LL < max(0LL, localEnd - localStart + 1LL);
}

int main() {
    vector<string> lines = readFileIntoVector("data.txt");
    vector<string> freshRanges;
    long long i = 0;
    long long result = 0;
    while (lines[i] != "") {
        freshRanges.push_back(lines[i++]);
    }

    set<pair<long long, long long>> rangeSet;

    for (auto&& str : freshRanges) {
        vector<string> split = splitByChar(str, '-');
        long long start = stoll(split[0]);
        long long end = stoll(split[1]);
        rangeSet.insert({start, end});
    }
restart:
    for (auto&& i : rangeSet) {
        for (auto&& j : rangeSet) {
            if (overlaps(i, j) && i != j) {
                long long newStart = min(i.first, j.first);
                long long newEnd = max(i.second, j.second);
                rangeSet.erase(i);
                rangeSet.erase(j);
                rangeSet.insert({newStart, newEnd});
                goto restart;
            }
        }
    }

    for (auto&& i : rangeSet) {
        result += i.second - i.first + 1;
    }

    cout << result << endl;
}