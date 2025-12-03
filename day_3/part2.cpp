#include <..\utils\aoc.h>

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Volt {
    int index;
    int value;
    Volt(int index, int value) {
        this->index = index;
        this->value = value;
    }

    bool operator>(const Volt& val) const {
        if (index > val.index) {
            return false;
        }
        return value >= val.value;
    }
};

int main() {
    vector<string> lines = readFileIntoVector("data.txt");

    long long result = 0;

    for (string& str : lines) {
        vector<Volt> rv;
        for (int i = str.length() - 12; i < str.length(); i++) {
            rv.push_back(Volt(i, str[i] - '0'));
        }

        for (int i = str.length() - 13; i > -1; i--) {
            Volt num = Volt(i, str[i] - '0');
            for (size_t j = 0; j < rv.size(); j++) {
                if (num > rv[j]) {
                    Volt temp = rv[j];
                    rv[j] = num;
                    num = temp;
                } else {
                    break;
                }
            }
        }

        long long res = 0;
        long long mul = 100000000000LL;

        for (auto&& i : rv) {
            res += i.value * mul;
            mul /= 10;
        }
        // cout << res << endl;
        result += res;
    }
    cout << result << endl;
}