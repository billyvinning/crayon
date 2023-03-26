#ifndef RAY_H
#define RAY_H

#include "vec.h"

typedef struct {
    Vec3 position;
    Vec3 direction;
} Ray;


Ray make_ray(double x, double y, double z, double u, double v, double w) {
    Ray r;
    Vec3 p = make_vec(x, y, z);
    Vec3 d = make_vec(u, v, w);

    r.position = p;
    r.direction = d;

    return r;
}

Vec3 propagate_ray(Ray r, double t) {
    Vec3 d = scale_vec(r.direction, t); 
    Vec3 result = add_vecs(r.position, d);
    return result;
}

#endif
