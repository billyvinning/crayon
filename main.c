#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>

#include "vec.h"
#include "ray.h"
#include "sphere.h"
#include "camera.h"


double get_rand(void) {
    return (float) rand() / (float) (RAND_MAX - 1);
}


Vec3 random_in_unit_sphere(void) {
    Vec3 p;
    do {
        p = sub_vecs(
                scale_vec(
                    make_vec(get_rand(), get_rand(), get_rand()),
                    2.0
                ),
            make_vec(1.0, 1.0, 1.0)
        );
    } while (dot_product(p, p) >= 1.0);
    return p;
}


bool has_hit_any_sphere(
    Sphere spheres[],
    int num_spheres,
    Ray r,
    double t_min,
    double t_max,
    HitRecord * rec
) {
    HitRecord temp_rec;
    bool has_hit_anything = false;
    double closest_t = t_max;
    for (int i = 0; i < num_spheres; i++) {
        bool has_hit = has_hit_sphere(
            spheres[i], r, t_min, closest_t, &temp_rec
        );
        if (has_hit) {
            has_hit_anything = true;
            closest_t = temp_rec.t;
            rec->normal = temp_rec.normal;
            rec->t = temp_rec.t;
            rec->p = temp_rec.p;
        }
    }
    return has_hit_anything;
}


Vec3 get_colour_vec(Ray r, Sphere spheres[], int num_spheres) {
    HitRecord rec;
    if (has_hit_any_sphere(spheres, num_spheres, r, 0.0, DBL_MAX, &rec)) {
        Vec3 target = add_vecs(
            add_vecs(
                rec.p,
                rec.normal
            ),
            random_in_unit_sphere()
        );
        Ray temp_ray = {rec.p, sub_vecs(target, rec.p)};
        Vec3 c = get_colour_vec(temp_ray, spheres, num_spheres);
        return scale_vec(c, 0.5);
    }
    else {
        Vec3 unit_direction = make_unit_vec(r.direction);
        double t = 0.5 * (unit_direction.y + 1.0);
        return add_vecs(
            scale_vec(
                make_vec(1.0, 1.0, 1.0),
                1.0 - t
            ),
            scale_vec(
                make_vec(0.5, 0.7, 1.0),
                t
            )
        );
    }
}


void simple_trace(int nx, int ny, int ns) {
    /* Propagate nx * ny rays from each pixel center backwards towards
     * the origin.
     */
    FILE * file;
    file = fopen("img.ppm", "w");

    fprintf(file, "P3\n%d %d\n255\n", nx, ny);
    int num_spheres = 2;
    Sphere spheres[] = {
        {make_vec(0.0, 0.0, -1.0), 0.5},
        {make_vec(0.0, -100.5, -1.0), 100.0}
    };
    Camera cam = {
        make_vec(0.0, 0.0, 0.0),
        make_vec(-2.0, -1.0, -1.0),
        make_vec(4.0, 0.0, 0.0),
        make_vec(0.0, 2.0, 0.0)
    };
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            Vec3 c = make_vec(0.0, 0.0, 0.0);
            for (int s = 0; s < ns; s++) {
                double u = ((double) i + get_rand()) / (double) nx;
                double v = ((double) j + get_rand()) / (double) ny;

                Ray r = get_ray(cam, u, v);
                c = add_vecs(
                    c, get_colour_vec(r, spheres, num_spheres)
                );
            }
            c = scale_vec(c, 1.0 / (double) ns);
            c = make_vec(sqrt(c.x), sqrt(c.y), sqrt(c.z));
            int ir = (int) 255.99 * c.x;
            int ig = (int) 255.99 * c.y;
            int ib = (int) 255.99 * c.z;
            fprintf(file, "%d %d %d\n", ir, ig, ib);
        }
    }
    fclose(file);
    return;

}

void make_gradient(int nx, int ny) {
    printf("P3\n%d %d\n255\n", nx, ny);
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            Vec3 c = make_vec(
                (double) i / (double) nx,
                (double) j / (double) ny,
                0.2
            );
            int ir = (int) c.x;
            int ig = (int) c.y;
            int ib = (int) c.z;
            printf("%d %d %d\n", ir, ig, ib);
        }
    }
    return;
}

int main(void) {
    simple_trace(200, 100, 100);
    return EXIT_SUCCESS;
}
