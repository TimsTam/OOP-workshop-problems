#include <iostream>
#include <vector>
#include <ctime>
#include <iomanip>
#include <cstdlib>
#include <limits>
#include <algorithm>

using namespace std;

class VectorOperationException: public exception {
    private:
        string message;
    public:
        VectorOperationException (const string &msg) : message(msg) {}
        const char *what() const throw() {
            return message.c_str();
        }
};

class VectorDivideByZero : public exception {
    private:
        string message;
    public:
        VectorDivideByZero (const string &msg) : message(msg) {}
        const char *what() const throw() {
            return message.c_str();
        }
};

class VectorMultiplicaton {
    public:
        vector<int> operator() (const vector<int> &v1, const vector<int> &v2) {
            if (v1.size() != v2.size()) {
                throw VectorOperationException("Muliplicaton cannot be performed due to different vector sizes");
            }
            vector<int> answer (v1.size());
            for(size_t i = 0; i < v1.size(); i++)
            {
                answer[i] = v1[i] * v2[i];
            }
        return answer;
        }
};

class VectorDivision {
    public:
        vector<int> operator() (const vector<int> &v1, const vector<int> &v2) {
            if (v1.size() != v2.size()) {
                throw VectorOperationException("Division cannot be performed due to different vector sizes");
            }
            vector<int> answer (v1.size());
            for(size_t i = 0; i < v1.size(); i++)
            {
                if (v2[i] == 0) {
                    throw VectorDivideByZero("Cannot divide by zero");
                }
                answer[i] = v1[i] / v2[i];
            }
        return answer;
        }
};

class NewVector {
    private:
        vector<int> data;
        VectorMultiplicaton multiply;
        VectorDivision divide;
    public:
        NewVector(int num_elem=10, vector<int> elements = {}) {
            if (elements.empty()) {
                for(int i=0; i < num_elem; i++) {
                data.push_back((rand() % 999) + 1);
                }
            } else {
                data = elements;
            }
        }
        NewVector(vector<int> elements) : data(elements) {}
        NewVector operator*(const NewVector &other) {
            data = multiply(data, other.data);
            return *this;
        }
        NewVector operator/(const NewVector &other) {
            data = divide(data, other.data);
            return *this;
        }
        friend ostream& operator<<(ostream& out, NewVector &v) {
            for (int val : v.data) {
                out << val << ", ";
            }
            out << endl;
            return out;
        }
};

int main() {
    cout << "Demo for vector operations" << endl;
    char QUIT = 'N';
    char MANUAL = 'b';
    int v1size, v2size;

    while (!(tolower(QUIT) == 'y'))
    {
        vector<int> vector1;
        vector<int> vector2;
        cout << "Input vector 1 size: ";
        cin >> v1size;
        cin.clear();
        cout << "Would you like manual input or auto input (m/a): ";
        cin >> MANUAL;
        cin.clear();
        while (!(tolower(MANUAL) == 'm') && !(tolower(MANUAL) == 'a')) {
            cout << "Invalid Input! Would you like manual input or auto input (m/a): ";
            cin >> MANUAL;
            cin.clear();
        }
        if (tolower(MANUAL) == 'm') {
            int temp;
            for (int i=0; i < v1size; i++) {
                cout << "Input index [" << i << "] for vector 1: ";
                cin >> temp;
                cin.clear();
                vector1.push_back(temp);
            }
        }
        cout << endl << "Input vector 2 size: ";
        cin >> v2size;
        cin.clear();
        cout << "Would you like manual input or auto input (m/a): ";
        cin >> MANUAL;
        cin.clear();
        while (!(tolower(MANUAL) == 'm') && !(tolower(MANUAL) == 'a')) {
            cout << "Invalid Input! Would you like manual input or auto input (m/a): ";
            cin >> MANUAL;
            cin.clear();
        }
        if (tolower(MANUAL) == 'm') {
            int temp;
            for (int i=0; i < v2size; i++) {
                cout << "Input index [" << i << "] for vector 2: ";
                cin >> temp;
                cin.clear();
                vector2.push_back(temp);
            }
        }
        NewVector v1(v1size, vector1);
        NewVector v2(v2size, vector2);
        cout << "Vector 1: " << v1;
        cout << "Vector 2: " << v2;

        try {
            NewVector v3 = v1 * v2;
            cout << endl << "Result of v1 * v2: ";
            cout << v3 << endl;
            v3 = v1 / v2;
            cout << endl << "Result of v1 / v2: ";
            cout << v3 << endl;
        }
        catch(VectorOperationException &e) {
            cout << "Vector Operation Error: " << e.what() << endl;
        }
        catch(VectorDivideByZero &e) {
            cout << "Vector Division Error: " << e.what() << endl;
        }
        catch(exception &e) {
            cout << "Standard Error: " << e.what() << '\n';
        }

        cout << "Quit y/n: ";
        cin >> QUIT;
        while (!(tolower(QUIT) == 'y') && !(tolower(QUIT) == 'n')) {
            cout << "Invalid input. Quit? y/n: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin >> QUIT;
        }
    }
}
