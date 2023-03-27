#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"
#include "vec.h"


typedef struct {
    Vec3 origin;
    Vec3 lower_left_corner;
    Vec3 horizontal;
    Vec3 vertical;
} Camera;


Ray get_ray(Camera c, double u, double v) {
    Vec3 direction = add_vecs(
        sub_vecs(
            c.lower_left_corner,
            c.origin
        ),
        add_vecs(
            scale_vec(c.horizontal, u),
            scale_vec(c.vertical, v)
        )
    );
    Ray r = {c.origin, direction};
    return r;
}


#endif
