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
        if (lines[i][0] == 'L') {
            counter -= stoi(lines[i].substr(1));
        } else {
            counter += stoi(lines[i].substr(1));
        }
        if (counter % 100 == 0) {
            result++;
        }
    }
    cout << result << endl;
}