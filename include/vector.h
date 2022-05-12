#ifndef _VECTOR_H_
#define _VECTOR_H_



double dot_product(const double a[], const double b[], unsigned int n);
void cross_product(const double a[3], const double b[3], double out[3]);
double mag2(const double a[], unsigned int n);
double mag(const double a[], unsigned int n);
void norm(const double a[], double out[], unsigned int n);
double cos_theta(const double a[], const double b[], unsigned int n);
double theta(const double a[], const double b[], unsigned int n);

#endif  // INCLUDE_VECTOR_H_"
