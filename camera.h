#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"
#include "vec.h"
#include "utils.h"


typedef struct {
    double lens_radius;
    Vec3 u;
    Vec3 v;
    Vec3 origin;
    Vec3 lower_left_corner;
    Vec3 horizontal;
    Vec3 vertical;
} Camera;


Camera make_camera(Vec3 lookfrom, Vec3 lookat, Vec3 vup, double vfov, double aspect, double aperture, double focus_dist) {
    double theta = vfov * PI / 180.0;
    double half_height = tan(theta / 2.0);
    double half_width = aspect * half_height;
    
    Vec3 origin = lookfrom;
    Vec3 w = make_unit_vec(sub_vecs(lookfrom, lookat));
    Vec3 u = make_unit_vec(cross_product(vup, w));
    Vec3 v = cross_product(w, u);

    Vec3 lower_left_corner = sub_vecs(
        origin,
        add_vecs(
            scale_vec(u, half_width * focus_dist),
            add_vecs(
                scale_vec(v, half_height * focus_dist),
                scale_vec(w, focus_dist)
            )
        )
    );
    Vec3 horizontal = scale_vec(u, 2.0 * half_width * focus_dist);
    Vec3 vertical = scale_vec(v, 2.0 * half_height * focus_dist);

    Camera c = {
        aperture / 2.0,
        u,
        v,
        origin,
        lower_left_corner,
        horizontal,
        vertical
    };

    return c;
}


Ray get_ray(Camera c, double u, double v) {
    Vec3 rd = scale_vec(random_in_unit_disk(), c.lens_radius);
    Vec3 offset = add_vecs(
        scale_vec(c.u, rd.x), scale_vec(c.v, rd.y)
    );

    Vec3 direction = sub_vecs(
        add_vecs(
            c.lower_left_corner,
            add_vecs(
                scale_vec(c.horizontal, u), scale_vec(c.vertical, v)
            )
        ),
        add_vecs(c.origin, offset)
    );

    Ray r = {add_vecs(c.origin, offset), direction};
    return r;
}


#endif
