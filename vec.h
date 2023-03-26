
typedef struct {
    double x;
    double y;
    double z;
} Vec3;


Vec3 make_vec(double x, double y, double z) {
    Vec3 v;

    v.x = x;
    v.y = y;
    v.z = z;

    return v;
}
