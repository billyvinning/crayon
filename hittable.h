#ifndef HITTABLE_H
#define HITTABLE_H

#include <stdbool.h>
#include "vec.h"
#include "material.h"


typedef struct {
    double t;
    Vec3 p;
    Vec3 normal;
    enum Material material;
    Vec3 albedo;
} HitRecord;


#endif
