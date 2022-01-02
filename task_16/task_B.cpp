#include <iostream>
#include <cstdlib>

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
};

class Vector {
    Point a;
    Point b;
    double EPS;

public:

    Vector(double EPS = 1e-5) {
        this->a = Point();
        this->b = Point();
        this->EPS = EPS;
    }

    Vector(Point a, Point b, double EPS = 1e-5) {
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

    bool has_intersection(Vector& other) {
        Point a = this->a;
        Point b = this->b;
        Point c = other.a;
        Point d = other.b;
        Vector ab(a, b);
        Vector ac(a, c);
        Vector ad(a, d);
        Vector ca(c, a);
        Vector cb(c, b);
        Vector cd(c, d);
        double ab_ac_ab_ad = ab.cross_product(ac) * ab.cross_product(ad);
        double cd_ca_cd_cb = cd.cross_product(ca) * cd.cross_product(cb);
        bool res = ab_ac_ab_ad <= 0 && cd_ca_cd_cb <= 0;
        bool lies_on_same_line = (abs(ab_ac_ab_ad) + abs(cd_ca_cd_cb)) < this->EPS;

        if (lies_on_same_line) {
            Point ab_square_left_corner(
                min(a.x, b.x),
                min(a.y, b.y)
            );
            Point ab_square_right_corner(
                max(a.x, b.x),
                max(a.y, b.y)
            );
            Point cd_square_left_corner(
                min(c.x, d.x),
                min(c.y, d.y)
            );
            Point cd_square_right_corner(
                max(c.x, d.x),
                max(c.y, d.y)
            );

            bool x_axis_no_intersection = ab_square_right_corner.x < cd_square_left_corner.x ||
                    cd_square_right_corner.x < ab_square_left_corner.x;
            bool y_axis_no_intersection = ab_square_right_corner.y < cd_square_left_corner.y ||
                    cd_square_right_corner.y < ab_square_left_corner.y;
            res = !x_axis_no_intersection && !y_axis_no_intersection;
        }
        
        return res;
    }

};

int main() {
    double point_a_x, point_a_y, point_b_x, point_b_y, point_c_x, point_c_y, point_d_x, point_d_y;
    std::ios_base::sync_with_stdio(false);

    cin >> point_a_x >> point_a_y >> point_b_x >> point_b_y;
    cin >> point_c_x >> point_c_y >> point_d_x >> point_d_y;

    Vector ab(
        Point(point_a_x, point_a_y),
        Point(point_b_x, point_b_y)
    );
    Vector cd(
        Point(point_c_x, point_c_y),
        Point(point_d_x, point_d_y)
    );

    bool res = ab.has_intersection(cd);

    cout << (res ? "YES" : "NO") << endl;

    return 0;
}