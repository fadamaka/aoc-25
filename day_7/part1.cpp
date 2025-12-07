#include <..\utils\aoc.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int countSplit(int y, int x, vector<string> v, int count) {
    if (y > v.size() - 1) {
        return count;
    }
    if (v[y - 1][x] == '.') {
        return countSplit(y - 1, x, v, count);
    }
    if (v[y - 1][x] == '^') {
        return countSplit(y - 1, x - 1, v, count) + countSplit(y - 1, x + 1, v, count) + 1;
    }
    return -1;
}

int main() {
    vector<string> lines = readFileIntoVector("data.txt");
    cout << countSplit(0, lines[0].find('S'), lines, 0) << endl;
}