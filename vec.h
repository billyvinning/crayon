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


double dot_product(Vec3 a, Vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}


double get_vec_norm_squared(Vec3 v) {
    return dot_product(v, v);
}


double get_vec_norm(Vec3 v) {
    return sqrt(get_vec_norm_squared(v));
}


Vec3 make_unit_vec(Vec3 v) {
    double norm = get_vec_norm(v);
    return make_vec(v.x / norm, v.y / norm, v.z / norm);
}

Vec3 scale_vec(Vec3 v, double t) {
    return make_vec(v.x * t, v.y * t, v.z * t);
}


Vec3 add_vecs(Vec3 a, Vec3 b) {
    return make_vec(
        a.x + b.x,
        a.y + b.y,
        a.z + b.z
    );
}


Vec3 sub_vecs(Vec3 a, Vec3 b) {
    return add_vecs(a, scale_vec(b, -1.0));

}


Vec3 reflect(Vec3 v, Vec3 n) {
    return sub_vecs(
        v,
        scale_vec(
            n,
            2.0 * dot_product(v, n)
        )
    );
}


Vec3 hadamard_product(Vec3 a, Vec3 b) {
    return make_vec(
        a.x * b.x, a.y * b.y, a.z * b.z
    );
}

#endif
