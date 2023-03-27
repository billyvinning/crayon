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


Camera make_camera(Vec3 lookfrom, Vec3 lookat, Vec3 vup, double vfov, double aspect) {
    double theta = vfov * 3.14159265358979323846 / 180.0;
    double half_height = tan(theta / 2.0);
    double half_width = aspect * half_height;
    
    Vec3 origin = lookfrom;
    Vec3 w = make_unit_vec(
        sub_vecs(lookfrom, lookat)
    );
    Vec3 u = make_unit_vec(cross_product(vup, w));
    Vec3 v = cross_product(w, u);

    Vec3 lower_left_corner = sub_vecs(
        origin,
        add_vecs(
            scale_vec(u, half_width),
            add_vecs(
                scale_vec(v, half_height),
                w
            )
        )
    );
    Vec3 horizontal = scale_vec(u, 2.0 * half_width);
    Vec3 vertical = scale_vec(v, 2.0 * half_height);

    Camera c = {
        origin,
        lower_left_corner,
        horizontal,
        vertical
    };

    return c;
}


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
