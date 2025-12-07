#include <..\utils\aoc.h>

#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

typedef long long i64;

map<pair<int, int>, i64> cache;

i64 countSplit(int y, int x, vector<string> v) {
    i64 count;
    if (cache.find({y + 1, x}) != cache.end()) {
        return cache[{y + 1, x}];
    }
    if (y + 1 > v.size() - 1) {
        count = 1;
    } else {
        if (v[y + 1][x] == '.') {
            count = countSplit(y + 1, x, v);
        }
        if (v[y + 1][x] == '^') {
            count = countSplit(y + 1, x - 1, v) + countSplit(y + 1, x + 1, v);
        }
    }
    cache.insert({{y + 1, x}, count});
    return count;
}

int main() {
    vector<string> lines = readFileIntoVector("data.txt");
    cout << countSplit(0, lines[0].find('S'), lines) << endl;
}