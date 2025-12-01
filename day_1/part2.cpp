#include <..\utils\aoc.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<string> lines = readFileIntoVector("data.txt");
    int counter = 50;
    int result = 0;
    for (size_t i = 0; i < lines.size(); i++) {
        result += stoi(lines[i].substr(1)) / 100;
        int turn = stoi(lines[i].substr(1)) % 100;
        if (lines[i][0] == 'L') {
            if (counter <= turn && counter != 0) {
                result++;
            }
            counter -= turn;
            if (counter < 0) {
                counter += 100;
            }
        } else {
            counter += turn;
            result += counter / 100;
            counter %= 100;
        }
    }
    cout << result << endl;
}