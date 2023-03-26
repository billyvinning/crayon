#include <stdio.h>
#include <stdlib.h>
#include "vec.h"
#include "ray.h"


Vec3 get_colour_vec(const Ray r) {
    Vec3 unit_direction = make_unit_vec(r.direction);
    double t = 0.5 * (unit_direction.y + 1.0);
    Vec3 v1 = scale_vec(make_vec(1.0, 1.0, 1.0), 1.0 - t);
    Vec3 v2 = scale_vec(make_vec(0.5, 0.7, 1.0), t);
    return add_vecs(v1, v2);
}


void simpleTrace(int nx, int ny) {
    printf("P3\n%d %d\n255\n", nx, ny);
    Vec3 lower_left_corner = make_vec(-2.0, -1.0, -1.0);
    Vec3 horizontal = make_vec(4.0, 0.0, 0.0);
    Vec3 vertical = make_vec(0.0, 2.0, 0.0);
    Vec3 position = make_vec(0.0, 0.0, 0.0);

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
            Vec3 c = get_colour_vec(r);
            int ir = (int) 255.99 * c.x;
            int ig = (int) 255.99 * c.y;
            int ib = (int) 255.99 * c.z;
            printf("%d %d %d\n", ir, ig, ib);
        }
    }
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
