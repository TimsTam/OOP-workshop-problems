#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath> // for std::pow and M_PI, for example M_PI * std::pow(radius, 2);

using namespace std;

class Point {
    private:
        double x;
        double y;
    public:
        Point(double xx = 0, double yy = 0) : x(xx), y(yy) {}
        Point(const Point& p) : x(p.x), y(p.y) {cout<<"Point: Copy constructor\n";}
        Point(Point&& p) : x(std::move(p.x)), y(std::move(p.y)) {
            cout<<"Point: Move constructor\n";
            p.x = 0; 
            p.y = 0; 
        }
        ~Point() {}
        Point& operator=(const Point& p) {
            cout<<"Point: Copy assignment\n";
            if (this != &p) {
                this->setx(p.x);
                this->sety(p.y);
            }
            return *this;
        }
        Point& operator=(Point&& p) {
            cout<<"Point: Move assignment\n";
            if (this != &p) {
                x = std::move(p.x);
                y = std::move(p.y);
                p.x = 0;
                p.y = 0;
            }
            return *this;
            }
        double getx() const {return x;}
        double gety() const {return y;}
        void setx(double xx) {x = xx;}
        void sety(double yy) {y = yy;}
};

class Circle {
    private:
        Point center;
        double radius;
    public:
        Circle(Point c, double r) : center(c), radius(r) {}
        Circle(const Circle& c) : center(c.center), radius(c.radius) {cout<<"Circle: Copy constructor\n";}
        Circle(Circle&& c) : center(std::move(c.center)), radius(c.radius) {
            cout<<"Circle: Move constructor\n";
            c.radius = 0;
        }
        ~Circle() {}
        Circle& operator=(const Circle& c) {
            cout<<"Circle: Copy assignment\n";
            if (this != &c) {
                this->setcenter(c.center);
                this->setradius(c.radius);
            }
            return *this;
        }
        Circle& operator=(Circle&& c) {
            cout<<"Circle: Move assignment\n";
            if (this != &c) {
                center = std::move(c.center);
                radius = std::move(c.radius);
                c.radius = 0;
            }
            return *this;
    }
        Point getcenter() const {return center;}
        double getradius() const {return radius;}
        void setcenter(Point c) {this->center = c;}
        void setradius(double r) {radius = r;}
        double calArea() const {return (M_PI * pow(radius, 2));}
        friend double operator+(const Circle& c1, const Circle& c2) {
            return c1.calArea() + c2.calArea();
        }
};

int main()
{
    Point p1(1.0, 1.0);
    Point p2(2.0, 2.0);

    cout << "output 1: " << endl;
    Circle c1(p1, 5.0);
    cout << endl;

    cout << "output 2: " << endl;
    Circle c2 = c1; // Test Point and Circle copy constructor
    cout << endl;

    cout << "output 3: " << endl;
    Circle c3(std::move(c1)); // Test Point and Circle move constructor
    cout << endl;

    cout << "output 4: " << endl;
    Circle c4(p2, 10.0);
    cout << endl;

    cout << "output 5: " << endl;
    c4 = c2; // Test copy assignment
    cout << endl;

    cout << "output 6: " << endl;
    c4 = std::move(c3); // Test move assignment
    cout << endl;

    cout << "output 7: " << endl;
    // Test friend function (addition of areas)
    double totalArea = c2 + c4;
    std::cout << "Total area of c2 and c4: " << totalArea << std::endl;

    return 0;
}
