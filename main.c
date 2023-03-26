#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>

#include "vec.h"
#include "ray.h"
#include "sphere.h"


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
    bool has_hit = has_hit_any_sphere(spheres, num_spheres, r, 0.0, DBL_MAX, &rec);
    if (has_hit) {
        return scale_vec(
            make_vec(
                rec.normal.x + 1.0,
                rec.normal.y + 1.0,
                rec.normal.z + 1.0
            ),
            0.5
        );
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

void simpleTrace(int nx, int ny) {
    /* Propagate nx * ny rays from each pixel center backwards towards
     * the origin.
     */
    FILE * file;
    file = fopen("img.ppm", "w");

    fprintf(file, "P3\n%d %d\n255\n", nx, ny);

    Vec3 lower_left_corner = make_vec(-2.0, -1.0, -1.0);
    Vec3 horizontal = make_vec(4.0, 0.0, 0.0);
    Vec3 vertical = make_vec(0.0, 2.0, 0.0);
    Vec3 position = make_vec(0.0, 0.0, 0.0);
    int num_spheres = 2;
    Sphere spheres[] = {
        {make_vec(0.0, 0.0, -1.0), 0.5},
        {make_vec(0.0, -100.5, -1.0), 100.0}
    };

    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            double u = (double) i / (double) nx;
            double v = (double) j / (double) ny;

            Vec3 direction = add_vecs(
                lower_left_corner,
                add_vecs(
                    scale_vec(horizontal, u),
                    scale_vec(vertical, v)
                )
            );
            Ray r = {position, direction};
            // Vec3 p = propagate_ray(r, 2.0);
            Vec3 c = get_colour_vec(r, spheres, num_spheres);
            int ir = (int) 255.99 * c.x;
            int ig = (int) 255.99 * c.y;
            int ib = (int) 255.99 * c.z;
            fprintf(file, "%d %d %d\n", ir, ig, ib);
        }
    }
    fclose(file);
    return;

}

void makeGradient(int nx, int ny) {
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
    simpleTrace(200, 100);
    return EXIT_SUCCESS;
}
