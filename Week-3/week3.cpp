#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

void read_numbers(vector<int> &numbers, string file_name = "input.txt");

bool greaterthan85(int i) {return i > 85;}

void changeValues(int& i) {
    if (i < 85)
        if (i < 75)
            if (i < 65)
                if (i < 50)
                    i = 3;
                else
                    i = 4;
            else
                i = 5;
        else
            i = 6;
    else
        i = 7;
}

void printNum(int i) {cout << i << ", ";}

float getAver(vector<int> v) {
    float average = 0;
    for (auto iter = v.begin(); iter != v.end(); iter++) {
        average += *iter;
    }
    average = average / v.size();
    return average;
}

int main()
{
    // Create a vector to store the integers read from the file
    std::vector<int> scores;
    read_numbers(scores, "input.txt");
    int count = count_if(scores.begin(), scores.end(), greaterthan85);
    cout << "Task1: Number of scores greater than 85: " << count << endl;
    sort(scores.begin(), scores.end());
    if (binary_search(scores.begin(), scores.end(), -1)) {
        cout << "Task2: Score -1 exits" << endl;
        auto newEnd = remove(scores.begin(), scores.end(), -1);
        scores.erase(newEnd, scores.end());
    } else {
        cout << "Task2: Score -1 doesn't exist" << endl;
    }

    cout << "Task3: Average scores after removing -1: " << getAver(scores) << endl;
    for_each(scores.begin(), scores.end(), changeValues);
    cout << "Task4: Average of updated scores: " << getAver(scores) << endl;
    return 0;
}

void read_numbers(vector<int> &numbers, string file_name)
{
    std::ifstream inputFile(file_name);
    if (!inputFile)
    {
        std::cerr << "Error: Could not open the file." << std::endl;
    }
    int num;
    while (inputFile >> num)
    {
        numbers.push_back(num);
    }
    inputFile.close();

    numbers.shrink_to_fit();
}