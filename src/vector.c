#include <vector.h>
#include <stdio.h>
#include <math.h>

#define _CROSS_PRODUCT_NDIM 3

double dot_product(const double a[], const double b[], unsigned int n) {
    double out = 0.0;
    unsigned int i;
    for (i = 0; i < n; i = i + 1) {
        out += a[i] * b[i];
    }
    return out;
}

void cross_product(const double a[_CROSS_PRODUCT_NDIM], const double b[_CROSS_PRODUCT_NDIM], double out[_CROSS_PRODUCT_NDIM]) {
    unsigned int i;
    for (i = 0; i < _CROSS_PRODUCT_NDIM; i = i + 1){
        unsigned int i_left = (i + 1) % _CROSS_PRODUCT_NDIM;
        unsigned int i_right = (i + 2) % _CROSS_PRODUCT_NDIM;
        out[i] = (a[i_left] * b[i_right]) - (a[i_right] * b[i_left]);
    }
}

double mag2(const double a[], unsigned int n) {
    double out = 0;
    unsigned int i;
    for (i = 0; i < n; i = i + 1) {
        out += pow(a[i], 2);
    }
    return out;
}

double mag(const double a[], unsigned int n) {
    return sqrt(mag2(a, n));
}

void norm(const double a[], double out[], unsigned int n) {
    unsigned int i;
    double _mag = mag(a, n);
    for (i = 0; i < n; i = i + 1) {
        out[i] = a[i] / _mag;
    }
}

double cos_theta(const double a[], const double b[], unsigned int n) {
    return dot_product(a, b, n) / (mag(a, n) * mag(b, n));
}

double theta(const double a[], const double b[], unsigned int n) {
    return acos(cos_theta(a, b, n));
}

