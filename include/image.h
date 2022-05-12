#ifndef _IMAGE_H_
#define _IMAGE_H_
#define _TEST_IMG_ROWS 2
#define _TEST_IMG_COLS 4
#define RGB_NDIM 3

void print_array(const int *array_2d, unsigned int num_rows, unsigned int num_cols);
void write_ppm(
        const int a[][RGB_NDIM],
        unsigned int rows,
        unsigned int cols,
        char* path
);
void test_img(int a[_TEST_IMG_COLS * _TEST_IMG_ROWS][RGB_NDIM]);

#endif  // INCLUDE_IMAGE_H_"
