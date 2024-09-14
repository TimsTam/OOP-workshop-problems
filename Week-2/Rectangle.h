#include <iostream>
#include <algorithm>
using namespace std;


class Rectangle {
    private:
        double width;
        double length;
        int x;
        int y;

    public:
        Rectangle(int xx = 0, int yy = 0, double w = 0, double l = 0);
        void setWidth(double);
        void setLength(double);
        double getWidth() const {return width;}
        double getLength() const {return length;}
        double getArea() const {return width * length;}
        bool operator<(const Rectangle& r) const;
        bool operator>(const Rectangle& r) const;
        bool operator==(const Rectangle& r) const;
        bool operator^(const Rectangle& r) const;
        Rectangle operator+(const Rectangle& r) const;
        double areaOfOverlap(const Rectangle& r) const;
        friend ostream& operator<<(ostream& out, const Rectangle& r);
    };

Rectangle::Rectangle(int xx, int yy, double w, double l) {
    width = w;
    length = l;
    x = xx;
    y = yy;
}

void Rectangle::setWidth(double w) {
    if (w >= 0)
        width = w;
    else {
        cout << "Invalid width\n";
        exit(EXIT_FAILURE);
    }
}

void Rectangle::setLength(double len)
{
    if (len >= 0)
        length = len;
    else {
        cout << "Invalid length\n";
        exit(EXIT_FAILURE);
    }
}

bool Rectangle::operator>(const Rectangle& r) const {
    double a1 = this->getArea();
    double a2 = r.getArea();
    return (a1 > a2);
}

bool Rectangle::operator<(const Rectangle& r) const {
    double a1 = this->getArea();
    double a2 = r.getArea();
    return (a1 < a2);
}

bool Rectangle::operator==(const Rectangle& r) const {
    double a1 = this->getArea();
    double a2 = r.getArea();
    return (a1 == a2);
}

bool Rectangle::operator^(const Rectangle& r) const {
    return ((x + width) < r.x || (r.x + r.width) < x || y < (r.y - r.length) || (r.y + r.length) < y);
}

Rectangle Rectangle::operator+(const Rectangle& r) const {
    double newWidth = (this->width + r.width) / 2;
    Rectangle rnew(this->x, this->y, newWidth, 0);
    rnew.setLength((this->getArea() + r.getArea()) / newWidth);
    return rnew;
}

double Rectangle::areaOfOverlap(const Rectangle& r) const {
    double overlapWidth = min(this->x + this->width, r.x + r.width) - max(this->x, r.x);
    double overlapLength = max(this->y, r.y) - max(this->y - this->length, r.y - r.length);
    return overlapWidth * overlapLength;
}

ostream& operator<<(ostream& out, const Rectangle& r) {
    out << "Coords: " << r.x << ", " << r.y << endl;
    out << "Width: " << r.width << endl;
    out << "Length: " << r.length << endl;
    out << "Area: " << r.getArea() << endl;
    return out;
}