#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

const double EPS = 1e-9;

class Point {
    double x;
    double y;
    friend class Vector;

public:

    Point() {
        this->x = 0;
        this->y = 0;
    }

    Point(double x, double y) {
        this->x = x;
        this->y = y;
    }

    Point operator+(Point& other) {
        Point res;
        res.x = this->x + other.x;
        res.y = this->y + other.y;
        return res;
    }

    Point operator-(Point& other) {
        Point res;
        res.x = this->x - other.x;
        res.y = this->y - other.y;
        return res;
    }

    Point operator*(double scalar) {
        Point res;
        res.x = scalar * this->x;
        res.y = scalar * this->y;
        return res;
    }

    Point operator/(double scalar) {
        Point res;
        res.x = this->x / scalar;
        res.y = this->y / scalar;
        return res;
    }
};

class Vector {
    Point a;
    Point b;
    double EPS;

public:

    Vector(double EPS = 1e-9) {
        this->a = Point();
        this->b = Point();
        this->EPS = EPS;
    }

    Vector(Point a, Point b, double EPS = 1e-9) {
        this->a = a;
        this->b = b;
        this->EPS = EPS;
    }

    Vector operator+(Vector& other) {
        Vector res;
        res.a = this->a;
        res.b = this->b + other.b - other.a;
        return res;
    }

    Vector operator-(Vector& other) {
        Vector res;
        res.a = this->a;
        res.b = this->b - other.b + other.a;
        return res;
    }

    Vector operator*(double scalar) {
        Vector res;
        res.a = this->a;
        res.b = this->b * scalar;
        return res;
    }

    double dot_product(Vector& other) {
        Point first_vector = this->b - this->a;
        Point second_vector = other.b - other.a;
        double res = first_vector.x * second_vector.x + first_vector.y * second_vector.y;
        return res;
    }

    double cross_product(Vector& other) {
        Point first_vector = this->b - this->a;
        Point second_vector = other.b - other.a;
        double res = first_vector.x * second_vector.y - first_vector.y * second_vector.x;
        return res;
    }
};

double get_area(Point& a, Point& b, Point& c) {
    Vector ab(a, b);
    Vector ac(a, c);
    double area = 0.5 * ab.cross_product(ac);
    return area;
}

int main() {
    int canvas_n;
    double point_x, point_y;
    double area = 0;
    std::ios_base::sync_with_stdio(false);
    cin >> canvas_n;
    cin >> point_x >> point_y;
    Point a(point_x, point_y);
    cin >> point_x >> point_y;
    Point b(point_x, point_y);

    for (int i = 0; i < canvas_n - 2; i++) {
        cin >> point_x >> point_y;
        Point c(point_x, point_y);
        area += get_area(a, b, c);
        b = c;
    }

    cout << abs(area) << endl;

    return 0;
}