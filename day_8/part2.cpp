#include <..\utils\aoc.h>

#include <algorithm>
#include <cfloat>
#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

typedef long long i64;

double findDistance(i64 x1, i64 y1, i64 z1, i64 x2, i64 y2, i64 z2) {
    double distance = hypot(hypot(x1 - x2, y1 - y2), z1 - z2);
    return distance;
}
double findDistance(tuple<i64, i64, i64> a, tuple<i64, i64, i64> b) {
    return findDistance(get<0>(a), get<1>(a), get<2>(a), get<0>(b), get<1>(b), get<2>(b));
}
tuple<i64, i64, i64> getNums(string str) {
    vector<string> split = splitByChar(str, ',');
    return make_tuple(stoi(split[0]), stoi(split[1]), stoi(split[2]));
}

string printTuple(tuple<i64, i64, i64> point) {
    return to_string(get<0>(point)) + "," + to_string(get<1>(point)) + "," + to_string(get<2>(point));
}

bool comp(tuple<size_t, size_t, double> a, tuple<size_t, size_t, double> b) {
    return get<2>(a) < get<2>(b);
}

void printSets(map<size_t, set<size_t>*> circuitMap) {
    set<set<size_t>*> circuitSet;
    for (auto&& i : circuitMap) {
        circuitSet.insert(i.second);
    }
    for (auto&& i : circuitSet) {
        cout << i->size() << ": ";
        for (auto&& j : *i) {
            cout << j << ", ";
        }
        cout << endl;
    }
}

size_t countCircuits(map<size_t, set<size_t>*> circuitMap) {
    set<set<size_t>*> circuitSet;
    for (auto&& i : circuitMap) {
        circuitSet.insert(i.second);
    }
    return circuitSet.size();
}

int main() {
    vector<string> lines = readFileIntoVector("data.txt");
    vector<tuple<i64, i64, i64>> coords;
    transform(lines.begin(), lines.end(), back_inserter(coords), [](const string& str) { return getNums(str); });

    // map<size_t, pair<size_t, double>> closestMap;
    // for (size_t i = 0; i < coords.size(); i++) {
    //     closestMap.insert({i, {i, DBL_MAX}});
    // }

    // for (size_t i = 0; i < coords.size(); i++) {
    //     for (size_t j = 0; j < coords.size(); j++) {
    //         if (i != j) {
    //             double mapDist = closestMap[i].second;
    //             double localDist = findDistance(coords[i], coords[j]);
    //             if (mapDist > localDist) {
    //                 closestMap[i] = {j, localDist};
    //             }
    //         }
    //     }
    // }
    vector<tuple<size_t, size_t, double>> distV;
    for (size_t i = 0; i < coords.size(); i++) {
        for (size_t j = 0; j < coords.size(); j++) {
            if (i != j) {
                distV.push_back(make_tuple(i, j, findDistance(coords[i], coords[j])));
            }
        }
    }
    // for (auto&& i : closestMap) {
    //     distV.push_back(make_tuple(i.first, i.second.first, i.second.second));
    // }
    sort(distV.begin(), distV.end(), comp);
    // cout << printTuple(coords[get<0>(distV[0])]) << " " << printTuple(coords[get<1>(distV[0])]) << endl;
    map<size_t, set<size_t>*> circuitMap;
    // set<size_t> setP;
    // setP.insert(2);
    // circuitMap.insert({0, &setP});
    // setP.insert(3);
    // circuitMap.insert({1, &setP});
    // circuitMap[0]->insert(4);
    // cout << setP.size() << " " << circuitMap[0]->size() << " " << circuitMap[1]->size() << endl;
    size_t prevA = 0;
    size_t prevB = 0;
    int connCount = 0;
    for (auto&& i : distV) {
        if (circuitMap.size() == 1000 && countCircuits(circuitMap) == 1) {
            break;
        }
        size_t aIndex = get<0>(i);
        size_t bIndex = get<1>(i);
        double distance = get<2>(i);
        if (prevA == bIndex && prevB == aIndex) {
            continue;
        }
        prevA = aIndex;
        prevB = bIndex;
        // cout << printTuple(coords[aIndex]) << " " << printTuple(coords[bIndex]) << " " << distance << endl;
        if (circuitMap.find(aIndex) == circuitMap.end() && circuitMap.find(bIndex) == circuitMap.end()) {
            set<size_t>* circuit = new set<size_t>();
            circuit->insert(aIndex);
            circuit->insert(bIndex);
            circuitMap.insert({aIndex, circuit});
            circuitMap.insert({bIndex, circuit});
            connCount++;
            // cout << printTuple(coords[aIndex]) << " " << printTuple(coords[bIndex]) << " " << distance << endl;
            // printSets(circuitMap);
            continue;
        }
        if (circuitMap.find(aIndex) != circuitMap.end() && circuitMap.find(bIndex) != circuitMap.end() && circuitMap[aIndex] == circuitMap[bIndex]) {
            connCount++;
            continue;
        }
        if (circuitMap.find(aIndex) != circuitMap.end() && circuitMap.find(bIndex) != circuitMap.end() && circuitMap[aIndex] != circuitMap[bIndex]) {
            circuitMap[aIndex]->insert(circuitMap[bIndex]->begin(), circuitMap[bIndex]->end());
            auto it = circuitMap[bIndex]->begin();
            auto end = circuitMap[bIndex]->end();
            for (; it != end; ++it) {
                circuitMap[*it] = circuitMap[aIndex];
            }

            connCount++;
            // cout << printTuple(coords[aIndex]) << " " << printTuple(coords[bIndex]) << " " << distance << endl;
            // cout << "merged" << endl;
            // printSets(circuitMap);
            continue;
        }
        if (circuitMap.find(aIndex) == circuitMap.end() && circuitMap.find(bIndex) != circuitMap.end()) {
            circuitMap[bIndex]->insert(aIndex);
            circuitMap.insert({aIndex, circuitMap[bIndex]});
            connCount++;
            // cout << printTuple(coords[aIndex]) << " " << printTuple(coords[bIndex]) << " " << distance << endl;
            // printSets(circuitMap);
            continue;
        }
        if (circuitMap.find(aIndex) != circuitMap.end() && circuitMap.find(bIndex) == circuitMap.end()) {
            circuitMap[aIndex]->insert(bIndex);
            circuitMap.insert({bIndex, circuitMap[aIndex]});
            connCount++;
            // cout << printTuple(coords[aIndex]) << " " << printTuple(coords[bIndex]) << " " << distance << endl;
            // printSets(circuitMap);
            continue;
        }
        throw "oops";
    }

    cout << get<0>(coords[prevA]) * get<0>(coords[prevB]) << endl;
}