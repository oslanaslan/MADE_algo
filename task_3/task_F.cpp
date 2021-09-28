#include <iostream>
#include <math.h>

using namespace std;

double EPS = 1e-10;
double MAX_SPEED_FACTOR = 1e5;
double PARAM_RANGE_LENGTH = 1;
double ITR = log(PARAM_RANGE_LENGTH * MAX_SPEED_FACTOR / EPS);

double journey_time(int forest_v, int field_v, double border, double enter_point) {
    border *= MAX_SPEED_FACTOR;
    enter_point *= MAX_SPEED_FACTOR;
    double field_way_length = sqrt((0 - enter_point) * (0 - enter_point) + (MAX_SPEED_FACTOR - border) * (MAX_SPEED_FACTOR - border));
    double forest_way_length = sqrt((MAX_SPEED_FACTOR - enter_point) * (MAX_SPEED_FACTOR - enter_point) + (0 - border) * (0 - border));

    return field_way_length / field_v + forest_way_length / forest_v;
}

int main() {
    int forest_v, field_v;
    double border;
    double left = 0;
    double right = PARAM_RANGE_LENGTH;

    cin >> field_v >> forest_v;
    cin >> border;

    for (int i = 0; i < ITR; i++) {
        double left_mid = left + (right - left) / 3;
        double right_mid = left + 2 * (right - left) / 3;
        double left_mid_element = journey_time(forest_v, field_v, border, left_mid);
        double right_mid_element = journey_time(forest_v, field_v, border, right_mid);

        if (left_mid_element < right_mid_element) {
            right = right_mid;
        }
        else {
            left = left_mid;
        }
    }

    printf("%8f\n", right);

    return 0;
}