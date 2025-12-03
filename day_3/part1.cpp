#include <..\utils\aoc.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    vector<string> lines = readFileIntoVector("data.txt");

    int result = 0;

    for (string& str : lines) {
        int max = 0;
        int maxIndex = 0;
        int second = 0;
        int secondIndex = 0;
        for (int i = 0; i < str.length(); i++) {
            int num = str[i] - '0';
            if (max < num) {
                second = max;
                secondIndex = maxIndex;

                max = num;
                maxIndex = i;
            }
        }
        if (maxIndex == str.length() - 1) {
            result += second * 10 + max;
            continue;
        }
        int secondMax = 0;
        for (int i = maxIndex + 1; i < str.length(); i++) {
            int num = str[i] - '0';
            if (num > secondMax) {
                secondMax = num;
            }
        }
        result += max * 10 + secondMax;
    }
    cout << result << endl;
}