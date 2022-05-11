#include <vector.h>
#include <stdio.h>
#include <math.h>

#define _CROSS_PRODUCT_N 3

double dot_product(double a[], double b[], int n) {
    double out = 0.0;
    int i;
    for (i = 0; i < n; i = i + 1) {
        out += a[i] * b[i];
    }
    return out;
}

void cross_product(double a[], double b[], double out[]) {
    int i, i_left, i_right;
    for (i = 0; i < _CROSS_PRODUCT_N; i = i + 1){
        i_left = (i + 1) % _CROSS_PRODUCT_N;
        i_right = (i + 2) % _CROSS_PRODUCT_N;
        out[i] = (a[i_left] * b[i_right]) - (a[i_right] * b[i_left]);
    }
}

double mag2(double a[], int n) {
    double out = 0;
    int i;
    for (i = 0; i < n; i = i + 1) {
        out += pow(a[i], 2);
    }
    return out;
}

double mag(double a[], int n) {
    return sqrt(mag2(a, n));
}

void norm(double a[], double out[], int n) {
    int i;
    double _mag = mag(a, n);
    for (i = 0; i < n; i = i + 1) {
        out[i] = a[i] / _mag;
    }
}

double cos_theta(double a[], double b[], int n) {
    return dot_product(a, b, n) / (mag(a, n) * mag(b, n));
}

double theta(double a[], double b[], int n) {
    return acos(cos_theta(a, b, n));
}

