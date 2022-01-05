#include <iostream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <list>
#include <set>

// На codeforces ловил ошибку компиляции, когда пытался достать M_PI из cmath
// Хотя локально работало. Поэтому задефайнил константу из документации к cmath
// # define M_PI           3.14159265358979323846  /* pi */
#define M_PI 3.141592653589793238462643383279502884L /* pi */
#define EPS 1e-10

using namespace std;

const double INF = 1e5;

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

    bool operator<(const Point other) const {
        return this->y == other.y ? this->x < other.x : this->y < other.y;
    }

    bool operator<=(const Point other) const {
        return this->y == other.y ? this->x <= other.x : this->y <= other.y;
    }

    bool operator>(const Point other) const {
        return this->y == other.y ? this->x > other.x : this->y > other.y;
    }

    bool operator>=(Point& other) const {
        return this->y == other.y ? this->x >= other.x : this->y >= other.y;
    }

    bool operator==(const Point other) const {
        return this->x == other.x && this->y == other.y;
    }

    bool operator!=(const Point other) const {
        return this->x != other.x || this->y != other.y;
    }

    double get_x() {
        return this->x;
    }

    double get_y() {
        return this->y;
    }

    double dist_to(Point& other) {
        double x_len = this->x - other.x;
        double y_len = this->y - other.y;
        return abs(sqrt(x_len * x_len + y_len * y_len));
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

    bool operator==(const Vector other) const {
        return (this->a == other.a && this->b == other.b);
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
        if (abs(angle) < EPS || abs(abs(angle) - M_PI) < EPS) {
            return abs(angle);
        }
        return angle;
    }

    double get_polar_angle() {
        if (this->a == this->b) {
            return INF;
        }
        double rad = atan2(this->b.y - this->a.y, this->b.x - this->a.x);

        if (rad < 0) {
            rad = 2 * M_PI + rad;
        }

        return rad;
    }

    double length() {
        double x_len = this->b.x - this->a.x;
        double y_len = this->b.y - this->a.y;
        return abs(sqrt(x_len * x_len + y_len * y_len));
    }
};

int main() {
    int canvas_n;
    double point_x, point_y;
    set<Point> point_set;
    list<Point> conv_hul;
    Point start_point;
    Point last_added_point, two_steps_ago_added_point;
    double perimeter = 0;

    cin >> canvas_n;
    
    // Read points
    for (int i = 0; i < canvas_n; i++) {
        cin >> point_x >> point_y;
        Point current_point(point_x, point_y);
        point_set.insert(current_point);
        start_point = (i == 0 || start_point > current_point ? current_point : start_point);
    }
    
    // point_set.erase(point_set.find(start_point));
    list<Point> point_vec(point_set.begin(), point_set.end());

    // Sort points with polar angle
    auto sort_comp = [&start_point](Point a, Point b) -> bool {
        Vector ca(start_point, a);
        Vector cb(start_point, b);
        double a_angle = ca.get_polar_angle();
        double b_angle = cb.get_polar_angle();

        if (abs(a_angle - b_angle) < EPS) {
            if (start_point.dist_to(a) <= start_point.dist_to(b)) {
                return true;
            }
            return false;
        }
        if (a_angle < b_angle) {
            return true;
        }
        return false;
    };
    point_vec.sort(sort_comp);

    // Create convex hull
    conv_hul.push_back(start_point);
    conv_hul.push_back(point_vec.front());
    two_steps_ago_added_point = start_point;
    last_added_point = point_vec.front();
    point_vec.pop_front();

    do {
        Point current_point = point_vec.front();
        Vector ab(two_steps_ago_added_point, last_added_point);
        Vector bc(last_added_point, current_point);
        double rotation = ab.get_angle(bc);

        if (rotation >= 0 || conv_hul.size() <= 1) {
            conv_hul.push_back(current_point);
            point_vec.pop_front();
            two_steps_ago_added_point = last_added_point;
            last_added_point = current_point;
        }
        else {
            conv_hul.pop_back();
            auto it = conv_hul.end();
            it--;
            last_added_point = *(it);
            it--;
            two_steps_ago_added_point = *(it);
        }
    }
    while (last_added_point != start_point);

    // Perimeter count
    Point prev_point = conv_hul.front();
    for (Point item : conv_hul) {
        perimeter += prev_point.dist_to(item);
        prev_point = item;
    }

    Vector ab(prev_point, conv_hul.front());
    perimeter += ab.length();

    cout << perimeter << endl;

    return 0;
}