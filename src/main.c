#include <stdio.h>
#include <vector.h>

main(){
    double a[3] = {1.0, 2.0, 3.0};
    double b[3] = {4.0, 5.0, 6.0};
    size_t n = sizeof(a);
    double c = dot_product(a, b, n);
    double d[3];
    cross_product(a, b, d);
    int i;
    for (i = 0; i < 3; i = i + 1) {
        printf("%f", d[i]);
    }
    printf("%f\n", d);
    
}
