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
            rec->material = temp_rec.material;
            rec->albedo = temp_rec.albedo;
        }
    }
    return has_hit_anything;
}


bool scatter_lambertian(Ray r, HitRecord rec, Vec3 * attenuation, Ray * scattered) {
    Vec3 target = add_vecs(
        add_vecs(
            rec.p,
            rec.normal
        ),
        random_in_unit_sphere()
    );
    Ray tmp = {rec.p, sub_vecs(target, rec.p)};
    scattered->position = tmp.position;
    scattered->direction = tmp.direction;
    attenuation->x = rec.albedo.x;
    attenuation->y = rec.albedo.y;
    attenuation->z = rec.albedo.z;
    return true;
}


bool scatter_metal(Ray r, HitRecord rec, Vec3 * attenuation, Ray * scattered){
    Vec3 reflected = reflect(
        make_unit_vec(r.direction),
        rec.normal
    );
    double fuzz = 1.0;
    reflected = add_vecs(
        reflected,
        scale_vec(
            random_in_unit_sphere(),
            fuzz
        )
    );
    Ray tmp = {rec.p, reflected}; 
    scattered->position = tmp.position;
    scattered->direction = tmp.direction;
    attenuation->x = rec.albedo.x;
    attenuation->y = rec.albedo.y;
    attenuation->z = rec.albedo.z;
    return dot_product(reflected, rec.normal) > 0;
}


double schlick(double cosine, double ref_idx) {
    double r0 = (1.0 - ref_idx) / (1.0 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1.0 - r0) * pow((1.0 - cosine), 5);
}


bool scatter_dielectric(Ray r, HitRecord rec, Vec3 * attenuation, Ray * scattered) {
    double ref_idx = 1.5;
    Vec3 outward_normal;
    Vec3 reflected = reflect(r.direction, rec.normal);
    double ni_over_nt;
    attenuation->x = 1.0;
    attenuation->y = 1.0;
    attenuation->z = 1.0;
    Vec3 refracted;
    double reflect_prob;
    double cosine;
    if (dot_product(r.direction, rec.normal) > 0) {
        outward_normal = scale_vec(rec.normal, -1.0);
        ni_over_nt = ref_idx;
        cosine = ref_idx * dot_product(r.direction, rec.normal) / get_vec_norm(r.direction);
    }
    else {
        outward_normal = rec.normal;
        ni_over_nt = 1.0 / ref_idx;
        cosine = -dot_product(r.direction, rec.normal) / get_vec_norm(r.direction);
    }
    if (refract(r.direction, outward_normal, ni_over_nt, &refracted)) {
        reflect_prob = schlick(cosine, ref_idx);
    }
    else {
        scattered->position = rec.p;
        scattered->direction = reflected;
        reflect_prob = 1.0;
    }
    if (get_rand() < reflect_prob) {
        scattered->position = rec.p;
        scattered->direction = reflected;
    }
    else {
        scattered->position = rec.p;
        scattered->direction = reflected;
    }

    return true;

}


Vec3 get_colour_vec(Ray r, Sphere spheres[], int num_spheres, int depth) {
    HitRecord rec;
    if (has_hit_any_sphere(spheres, num_spheres, r, 0.001, DBL_MAX, &rec)) {
        Ray scattered;
        Vec3 attenuation;
        bool is_scatter = false;
        switch (rec.material) {
            case LAMBERTIAN:
                is_scatter = scatter_lambertian(r, rec, &attenuation, &scattered);
                break;
            case METAL:
                is_scatter = scatter_metal(r, rec, &attenuation, &scattered);
                break;
            case DIELECTRIC:
                is_scatter = scatter_dielectric(r, rec, &attenuation, &scattered);
                break;
        }
        if (depth < 50 && is_scatter) {
            return hadamard_product(
                attenuation,
                get_colour_vec(scattered, spheres, num_spheres, depth+1)
            ); 
        }
        else {
            return make_vec(0.0, 0.0, 0.0);
        }    
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
    int num_spheres = 4;
    Sphere spheres[] = {
        {
            make_vec(0.0, 0.0, -1.0),
            0.5,
            LAMBERTIAN,
            make_vec(0.1, 0.2, 0.5)
        },
        {
            make_vec(0.0, -100.5, -1.0),
            100.0,
            LAMBERTIAN,
            make_vec(0.8, 0.8, 0.0)
        },
        {
            make_vec(1.0, 0.0, -1.0),
            0.5,
            METAL,
            make_vec(0.8, 0.6, 0.2)
        },
        {
            make_vec(-1.0, 0.0, -1.0),
            0.5,
            DIELECTRIC,
            make_vec(0.0, 0.0, 0.0)
        }
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
                    c, get_colour_vec(r, spheres, num_spheres, 0)
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
