#ifndef UTILS_H
#define UTILS_H

#include <math.h>


double PI = 3.14159265358979323846;


double get_rand(void) {
    return (float) rand() / (float) (RAND_MAX - 1);
}

#endif
