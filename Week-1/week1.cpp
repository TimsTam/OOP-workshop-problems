#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
using namespace std;

int printVector (vector<int>& vec) {
    for (int i=0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;
    return 0;
}

template <class T>
int calculateStats (vector<T>& vec) {
    float sum = 0;
    auto max = INT_MIN;
    auto min = INT_MAX;
    for (auto num : vec) {
        sum += num;
        if (num > max) {max = num;}
        if (num < min) {min = num;}
    }
    cout << "Maximum: " << max << endl;
    cout << "Minimum: " << min << endl;
    cout << "Average: " << sum / vec.size() << endl;
    return 0;
}

int main () {
    fstream file;
    vector<int> v;
    string line;
    file.open("input.txt");
    if (!file.is_open()) {
        cout << "Error opening file!" << endl;
        return 1;
    }
    while (getline(file, line)) {
            v.push_back(stoi(line));
    }
    file.close();
    printVector(v);
    calculateStats(v);
}