#include <iostream>
#include <cstdlib>

using namespace std;

double EPS = 1e-5;

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

public:

    Vector() {
        this->a = Point();
        this->b = Point();
    }

    Vector(Point a, Point b) {
        this->a = a;
        this->b = b;
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

int main() {
    double point_a_x, point_a_y, point_b_x, point_b_y, point_c_x, point_c_y;
    std::ios_base::sync_with_stdio(false);

    cin >> point_a_x >> point_a_y >> point_b_x >> point_b_y >> point_c_x >> point_c_y;

    Point a(point_a_x, point_a_y);
    Point b(point_b_x, point_b_y);
    Point c(point_c_x, point_c_y);
    Vector ab(a, b);
    Vector ac(a, c);
    double cross_prod = ab.cross_product(ac);
    double dot_prod = ab.dot_product(ac);

    if (abs(cross_prod) < EPS && dot_prod <= 0) {
        cout << "YES" << endl;
    }
    else {
        cout << "NO" << endl;
    }

    return 0;
}