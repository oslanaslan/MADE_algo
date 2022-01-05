#include <iostream>
#include <cstdlib>
#include <cmath>

// На codeforces ловил ошибку компиляции, когда пытался достать M_PI из cmath
// Хотя локально работало. Поэтому задефайнил константу из документации к cmath
// # define M_PI           3.14159265358979323846  /* pi */
#define M_PI 3.141592653589793238462643383279502884L /* pi */
#define EPS 1e-5

using namespace std;

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

    bool operator==(const Point other) const {
        if (this->x == other.x && this->y == other.y) {
            return true;
        }
        return false;
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

    double get_angle(Vector& other) {
        double cross_prod = this->cross_product(other);
        double dot_prod = this->dot_product(other);
        double angle = atan2(cross_prod, dot_prod);
        return angle;
    }

    bool lies_on_vector(Point a) {
        Point b = this->a;
        Point c = this->b;

        if (a == b || a == c) {
            return true;
        }

        Vector ba(b, a);
        Vector ca(c, a);
        Vector bc(b, c);
        double cross_prod_1 = ba.cross_product(bc);
        double cross_prod_2 = ca.cross_product(bc);
        double dot_prod_1 = ba.dot_product(bc);
        double dot_prod_2 = ca.dot_product(bc);

        if (abs(cross_prod_1) < EPS && abs(cross_prod_2) < EPS && dot_prod_1 > 0 && dot_prod_2 < 0) {
            return true;
        }

        return false;
    }
};

int main() {
    int canvas_n;
    double point_x, point_y;
    double angle = 0;
    std::ios_base::sync_with_stdio(false);
    cin >> canvas_n >> point_x >> point_y;
    Point target_point(point_x, point_y);
    cin >> point_x >> point_y;
    Point first_point(point_x, point_y);
    Point very_first_point = first_point;

    for (int i = 0; i < canvas_n - 1; i++) {
        cin >> point_x >> point_y;
        Point second_point(point_x, point_y);
        Vector ab(target_point, first_point);
        Vector ac(target_point, second_point);
        Vector bc(first_point, second_point);
        angle += ac.get_angle(ab);

        if (bc.lies_on_vector(target_point)) {
            cout << "YES" << endl;
            return 0;
        }

        first_point = second_point;
    }

    Vector ab(target_point, first_point);
    Vector ac(target_point, very_first_point);
    Vector bc(first_point, very_first_point);

    if (bc.lies_on_vector(target_point)) {
        cout << "YES" << endl;
    }
    else {
        angle += ac.get_angle(ab);
        bool res = abs(abs(angle) - 2 * M_PI) < EPS;

        cout << (res ? "YES" : "NO") << endl;
    }

    return 0;
}