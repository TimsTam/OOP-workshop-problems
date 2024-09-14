#include <iostream>
#include "Rectangle.h"
using namespace std;

int main() {
    cout << boolalpha << endl;
    Rectangle r1(0, 0, 3, 4);
    cout << "Task1: rectangle r1: \n" << r1 << endl;
    Rectangle r2(1, 2, 3, 2);
    cout << "Task2: r1 < r2: " << (r1 < r2) << endl;
    cout << "Task3: r1 == r2: " << (r1 == r2) << endl;
    cout << "Task4: r1 > r2: " << (r1 > r2) << endl;
    cout << "Task5: r1 ^ r2: " << (r1 ^ r2) << endl << endl;
    cout << "Task6: r1 + r2: \n" << (r1 + r2) << endl;
    cout << "Area of overlap: " << r1.areaOfOverlap(r2) << endl << endl;
    return 0;
}
