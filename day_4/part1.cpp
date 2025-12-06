#include <..\utils\aoc.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

int checkNeighbour(vector<string> lines, int i, int j);

int main() {
    vector<string> lines = readFileIntoVector("data.txt");
    int sum = 0;
    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines[i].size(); j++) {
            if (lines[i][j] == '@') {
                if (checkNeighbour(lines, i, j) < 4) {
                    sum++;
                }
            }
        }
    }

    cout << "result: " << sum << endl;
}

int checkNeighbour(vector<string> lines, int i, int j) {
    int sum = 0;
    /*
    ###
    #N#
    ##T
    */
    if (i + 1 < lines.size() && j + 1 < lines[i].size()) {
        if (lines[i + 1][j + 1] != '.') {
            sum++;
        }
    }
    /*
    T##
    #N#
    ###
    */
    if (i - 1 >= 0 && j - 1 >= 0) {
        if (lines[i - 1][j - 1] != '.') {
            sum++;
        }
    }

    /*
    ###
    #N#
    T##
    */
    if (i + 1 < lines.size() && j - 1 >= 0) {
        if (lines[i + 1][j - 1] != '.') {
            sum++;
        }
    }
    /*
    ##T
    #N#
    ###
    */
    if (i - 1 >= 0 && j + 1 < lines[i].size()) {
        if (lines[i - 1][j + 1] != '.') {
            sum++;
        }
    }
    /*
    #T#
    #N#
    ###
    */
    if (i - 1 >= 0) {
        if (lines[i - 1][j] != '.') {
            sum++;
        }
    }
    /*
    ###
    #N#
    #T#
    */
    if (i + 1 < lines.size()) {
        if (lines[i + 1][j] != '.') {
            sum++;
        }
    }
    /*
    ###
    #NT
    ###
    */
    if (j + 1 < lines[i].size()) {
        if (lines[i][j + 1] != '.') {
            sum++;
        }
    }
    /*
    ###
    TN#
    ###
    */
    if (j - 1 >= 0) {
        if (lines[i][j - 1] != '.') {
            sum++;
        }
    }

    return sum;
}