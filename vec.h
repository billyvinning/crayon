#ifndef VEC_H
#define VEC_H

#include <math.h>

typedef struct {
    double x;
    double y;
    double z;
} Vec3;


Vec3 make_vec(double x, double y, double z) {
    Vec3 v;

    v.x = x;
    v.y = y;
    v.z = z;

    return v;
}


double get_vec_norm_squared(Vec3 v) {
    return pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2); 
}


double get_vec_norm(Vec3 v) {
    return pow(get_vec_norm_squared(v), 0.5);
}


Vec3 make_unit_vec(Vec3 v) {
    double norm = get_vec_norm(v);
    return make_vec(v.x / norm, v.y / norm, v.z / norm);
}

Vec3 scale_vec(Vec3 v, double t) {
    Vec3 result = make_vec(v.x * t, v.y * t, v.z * t);
    return result;
}


Vec3 add_vecs(Vec3 a, Vec3 b) {
    Vec3 result = make_vec(
        a.x + b.x,
        a.y + b.y,
        a.z + b.z
    );
    return result;
}


#endif
