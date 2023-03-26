#include <stdio.h>
#include <stdlib.h>

void makeGradient(int nx, int ny) {
    printf("P3\n%d %d\n255\n", nx, ny);
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            double r = (double) i / (double) nx;
            double g = (double) j / (double) ny;
            double b = 0.2;
            int ir = (int) 255.99 * r;
            int ig = (int) 255.99 * g;
            int ib = (int) 255.99 * b;
            printf("%d %d %d\n", ir, ig, ib);
        }
    }
    return;
}

int main(void) {
    makeGradient(200, 100);
    return EXIT_SUCCESS;
}
