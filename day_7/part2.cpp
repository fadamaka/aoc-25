#include <..\utils\aoc.h>

#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

map<pair<int, int>, long long> cache;

long long countSplit(int y, int x, vector<string> v, long long count) {
    if (cache.find({y + 1, x}) != cache.end()) {
        return cache[{y + 1, x}];
    }
    if (y + 1 > v.size() - 1) {
        cache.insert({{y + 1, x}, 1});
        return 1LL;
    }
    if (v[y + 1][x] == '.') {
        count = countSplit(y + 1, x, v, count);
        cache.insert({{y + 1, x}, count});
        return count;
    }
    if (v[y + 1][x] == '^') {
        // cout << "split at y: " << y + 1 << " x: " << x << endl;
        count = countSplit(y + 1, x - 1, v, count) + countSplit(y + 1, x + 1, v, count);
        cache.insert({{y + 1, x}, count});
        return count;
    }
    throw "oops";
}

int main() {
    vector<string> lines = readFileIntoVector("data.txt");
    cout << countSplit(0, lines[0].find('S'), lines, 0LL) << endl;
}