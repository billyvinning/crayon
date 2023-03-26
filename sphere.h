#ifndef SPHERE_H
#define SPHERE_H

#include <stdbool.h>
#include "vec.h"
#include "hittable.h"
#include "ray.h"

typedef struct {
    Vec3 center;
    double radius;
} Sphere;


bool has_hit_sphere(Sphere s, Ray r, double t_min, double t_max, HitRecord * rec) {
    Vec3 oc = sub_vecs(r.position, s.center);
    double a = dot_product(r.direction, r.direction);
    double b = dot_product(oc, r.direction);
    double c = dot_product(oc, oc) - (s.radius * s.radius);
    double discriminant = (b * b) - (a * c);
    if (discriminant > 0) {
        double tmp = (-b - sqrt((b * b) - (a * c))) / a;
        if (tmp < t_max && tmp > t_min) {
            rec->t = tmp;
            rec->p = propagate_ray(r, rec->t);
            Vec3 normal = scale_vec(
                sub_vecs(rec->p, s.center), 1.0 / s.radius
            );
            rec->normal = normal;
            return true;
        }
        tmp = (-b + sqrt((b * b) - (a * c))) / a;
        if (tmp < t_max && tmp > t_min) {
            rec->t = tmp;
            rec->p = propagate_ray(r, rec->t);
            Vec3 normal = scale_vec(
                sub_vecs(rec->p, s.center), 1.0 / s.radius
            );
            rec->normal = normal;
            return true;
        }

    }

    return false;
}


#endif
