#include <..\utils\aoc.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int checkNeighbour(vector<string> lines, int i, int j);

int main() {
    vector<string> lines = readFileIntoVector("data.txt");
    int sum = 1;
    int res = 0;
    while (sum > 0) {
        sum = 0;
        for (int i = 0; i < lines.size(); i++) {
            for (int j = 0; j < lines[i].size(); j++) {
                if (lines[i][j] == '@') {
                    if (checkNeighbour(lines, i, j) < 4) {
                        sum++;
                        lines[i][j] = '.';
                    }
                }
            }
        }
        res += sum;
    }

    cout << "result: " << res << endl;
}

int checkNeighbour(vector<string> lines, int i, int j) {
    int sum = 0;
    int dir[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {-1, 1}, {0, -1}};

    for (size_t x = 0; x < 8; x++) {
        if (i + dir[x][0] < lines.size() && j + dir[x][1] < lines[i].size()) {
            if (lines[i + dir[x][0]][j + dir[x][1]] != '.') {
                sum++;
            }
        }
    }

    return sum;
}