#ifndef HITTABLE_H
#define HITTABLE_H

#include <stdbool.h>
#include "vec.h"

typedef struct {
    double t;
    Vec3 p;
    Vec3 normal;
} HitRecord;


#endif
