#ifndef _VECTOR_H_
#define _VECTOR_H_

//struct vec3 {
//    double[3] position;
//    double[3] direction;
//    double t;
//}

double dot_product(double a[], double b[], int n);
void cross_product(double a[], double b[], double out[]);
double mag2(double a[], int n);
double mag(double a[], int n);
void norm(double a[], double out[], int n);
double cos_theta(double a[], double b[], int n);
double theta(double a[], double b[], int n);

#endif
