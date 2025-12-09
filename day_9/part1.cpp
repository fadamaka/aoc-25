#include <..\utils\aoc.h>

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef long long i64;

typedef pair<i64, i64> point;

int main() {
    vector<string> lines = readFileIntoVector("data.txt");
    vector<point> pVec;
    for (size_t i = 0; i < lines.size(); i++) {
        vector<string> split = splitByChar(lines[i], ',');
        pVec.push_back({stoll(split[0]), stoll(split[1])});
    }

    i64 highest = 0;
    for (size_t i = 0; i < pVec.size(); i++) {
        for (size_t j = i + 1; j < pVec.size(); j++) {
            point a = pVec[i];
            point b = pVec[j];

            i64 tiles = (abs(a.first - b.first) + 1) * (abs(a.second - b.second) + 1);
            if (highest < tiles) {
                highest = tiles;
            }
        }
    }
    cout << highest << endl;
}