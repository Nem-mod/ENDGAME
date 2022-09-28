#include "../inc/gamemath.h"

int mx_rand(int min, int max) {
    if (min > max) {
        int temp = max;
        max = min;
        min = temp;
    }
    return rand() % (max - min + 1) + min;
}

bool mx_chance(int percent) {
    return mx_rand(0, 100) < percent ? true : false;
}

int mx_percent_from_int(int num, int percent) {
    return num * 100 / percent;
}

int mx_int_dispersion(int num, int percent) {
    int sign = 1;

    if (mx_chance(50))
        sign = -1;
    return num + (mx_percent_from_int(num, mx_rand(0, percent))) * sign;
}
